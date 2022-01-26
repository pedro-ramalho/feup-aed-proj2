#include "../../headers/graphs/distancegraph.h"

DistanceGraph::DistanceGraph(const Stops& stops, const Lines& lines, int num, double distance) : n(num), nodes(num + 1) {
    this->distance = distance;
    this->build_graph(stops, lines, distance);
}


void DistanceGraph::connect_nearby_stops(const Stops& stops, int curr_node_id, double distance) {
    int size = this->nodes.size();
    for (int j = 1; j < size; j++)                
        if (curr_node_id != j && haversine(stops.get_coords(curr_node_id), stops.get_coords(j)) <= distance) {
            this->add_edge(curr_node_id, j, haversine(stops.get_coords(curr_node_id), stops.get_coords(j)), "A pé"); 
        }
}

void DistanceGraph::build_graph(const Stops& stops, const Lines& lines, double distance) {
    std::string curr_line;
    std::pair<double, double> src_coords, dest_coords;

    int src_stop_id, dest_stop_id;
    double dist;

    for (const std::string path : lines.get_line_paths()) {
        std::vector<std::string> codes = lines.get_line_stops(path);
        std::string curr_line;

        if (codes.empty()) continue;

        for (int i = 1; i < codes.size(); i++) {
            src_stop_id = stops.get_id(codes[i - 1]);
            dest_stop_id = stops.get_id(codes[i]);
            
            
            src_coords = stops.get_coords(src_stop_id);
            dest_coords = stops.get_coords(dest_stop_id);
            distance = haversine(src_coords, dest_coords);

            curr_line = path.substr(8, path.size() - 12); 

            this->add_edge(src_stop_id, dest_stop_id, distance, curr_line);
        }
    }
}



void DistanceGraph::add_edge(int src, int dest, double weight, std::string line) {
    if (src < 1 || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({line, weight, dest});
}


//dijkstra original - tem de se mudar para o pretendido
void DistanceGraph::dijkstra(int s) {
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
std::list<int> DistanceGraph::dijkstra_path(int src, int dest) {
    std::cout << "Entrei no dijkstra path" << std::endl;
    dijkstra(src);
    std::cout << "Fiz o dijkstra(src)" << std::endl;
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


std::vector<DistanceNode> DistanceGraph::get_nodes() {
    return this->nodes;
}