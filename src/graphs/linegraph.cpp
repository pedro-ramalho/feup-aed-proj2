#include "../../headers/graphs/linegraph.h"

LineGraph::LineGraph(const StopsAndLines& stops_and_lines, int num, double distance) : n(num), nodes(num + 1) {
    this->n = num;
    this->distance = distance;
    this->build_graph(stops_and_lines, distance);
}


void LineGraph::connect_nearby_stops(const StopsAndLines& stops_and_lines, int curr_node_id, double distance) {

}

void LineGraph::build_graph(const StopsAndLines& stops_and_lines, double distance) {
    std::ifstream file;
    std::string word1;
    std::string word2;
    std::string curr_line;

    for (const std::string path : stops_and_lines.get_line_paths()) {
        curr_line = path.substr(8, path.size() - 12); 
        file.open(path);
    
        std::getline(file, word1); //gets the number of lines
        int num_stops = std::stoi(word1);
        if (num_stops == 0) continue;

        std::getline(file, word1);

        while (std::getline(file, word2)) {
            int src = stops_and_lines.get_stop_line_id(word1, curr_line);
            int dest = stops_and_lines.get_stop_line_id(word2, curr_line);
            this->add_edge(src, dest , 0, curr_line);
            word1 = word2;
        }
        
        file.close();
    }

}

void LineGraph::add_edge(int src, int dest, int weight, std::string line) {
    if (src < 1 || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({line, dest, weight});
}

//dijkstra original - tem de se mudar para o pretendido
void LineGraph::dijkstra(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].dist = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }
        }
    }
}


//dijkstra path original - tem de se mudar para o pretendido
std::list<int> LineGraph::dijkstra_path(const StopsAndLines& stops_and_lines, int src, int dest) {
    dijkstra(src);
    std::list<int> path;
    if (nodes[dest].dist == INF) return path;
    path.push_back(dest);
    int v = dest;
    while (v != src) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}


std::vector<LineNode> LineGraph::get_nodes() {
    return this->nodes;
}