#include "../../headers/graphs/linegraph.h"

LineGraph::LineGraph(const StopsAndLines& stops_and_lines, int num, double distance) : n(num), nodes(num + 1) {
    this->distance = distance;
    this->build_graph(stops_and_lines, distance);
    for (int i = 1; i <= 5262; i++) {
        for (auto e : nodes[i].adj)
        std::cout << "i: " << i << " e.line = " << e.line << " e.dest = " << e.dest << " e.weight = " << e.weight << std::endl;
    }
}


void LineGraph::connect_nearby_stops(const StopsAndLines& stops_and_lines, int curr_node_id, double distance) {
    if (this->nodes[curr_node_id].connected_nearby_stops) return;
    int size = this->nodes.size();
    for (int j = 1; j < size; j++)                
        if (curr_node_id != j && haversine(stops_and_lines.get_coords(curr_node_id), stops_and_lines.get_coords(j)) <= distance) {
            int weight;
            std::string line1 = stops_and_lines.get_line(curr_node_id);
            std::string line2 = stops_and_lines.get_line(j);
            weight = line1.substr(0, line1.size() - 2) == line2.substr(0, line2.size() - 2) ? 0 : 1;
            this->add_edge(curr_node_id, j, weight, "A pé");
            this->nodes[curr_node_id].connected_nearby_stops = true;
            //std::cout << haversine(stops.get_coords(curr_node_id), stops.get_coords(j)) << std::endl;
        }
}


void LineGraph::connect_begin_and_end_stops(const StopsAndLines& stops_and_lines, int curr_node_id) {
    int size = this->nodes.size();
    for (int j = 1; j < size; j++)                
        if (stops_and_lines.get_code_line(curr_node_id).first == stops_and_lines.get_code_line(j).first && curr_node_id != j) {
            this->add_edge(curr_node_id, j, 0, "A pé");
            this->nodes[curr_node_id].connected_nearby_stops = true;
            //std::cout << haversine(stops.get_coords(curr_node_id), stops.get_coords(j)) << std::endl;
        }
}


void LineGraph::build_graph(const StopsAndLines& stops_and_lines, double distance) {
    std::ifstream file;
    std::string word1;
    std::string word2;
    std::string curr_line;

    for (const std::string path : stops_and_lines.get_line_paths()) {
        curr_line = path.substr(8, path.size() - 12);
        std::vector<std::string> codes = stops_and_lines.get_codes(path); 
        file.open(path);

        if (codes.empty()) continue;

        for (int i = 1; i < codes.size(); i++) {
            int src_stop_id = stops_and_lines.get_stop_line_id(codes[i - 1], curr_line);
            int dest_stop_id = stops_and_lines.get_stop_line_id(codes[i], curr_line);
            curr_line = path.substr(8, path.size() - 12);
            this->add_edge(src_stop_id, dest_stop_id, 0, curr_line);
        }
    
        // std::getline(file, word1); //gets the number of lines
        // int num_stops = std::stoi(word1);
        // if (num_stops == 0) continue;

        // std::getline(file, word1);

        // while (std::getline(file, word2)) {
        //     int src = stops_and_lines.get_stop_line_id(word1, curr_line);
        //     int dest = stops_and_lines.get_stop_line_id(word2, curr_line);
        //     this->add_edge(src, dest , 0, curr_line);
        //     word1 = word2;
        // }
        
        file.close();
    }
}

void LineGraph::add_edge(int src, int dest, int weight, std::string line) {
    if (src < 1 || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({line, dest, weight});
}

//dijkstra original - tem de se mudar para o pretendido
void LineGraph::dijkstra(const StopsAndLines& stops_and_lines, int s, int end) {
    MinHeap<int, int> q(n, -1);

    for (int v=1; v<=n; v++) {
        nodes[v].dist = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
        nodes[v].connected_nearby_stops = false;
    }
    
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    nodes[s].distance_available = this->distance;
    nodes[s].line_used = "A pé";

    connect_begin_and_end_stops(stops_and_lines, s);
    connect_begin_and_end_stops(stops_and_lines, end);

    while (q.getSize()>0) {
        int u = q.removeMin();
        this->connect_nearby_stops(stops_and_lines, u, nodes[u].distance_available);
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
                nodes[v].line_used = e.line;
                nodes[v].distance_available = e.line == "A pé" ? nodes[u].distance_available - haversine(stops_and_lines.get_coords(u), stops_and_lines.get_coords(v)) : nodes[u].distance_available;
            }
        }
    }
}


//dijkstra path original - tem de se mudar para o pretendido
std::pair<int, std::list<int>> LineGraph::dijkstra_distance_path(const StopsAndLines& stops_and_lines, int src, int dest) {
    dijkstra(stops_and_lines, src, dest);
    std::list<int> path;
    if (nodes[dest].dist == INF) return {std::make_pair(-1, path)};
    path.push_back(dest);
    int v = dest;
    while (v != src) {
        v = nodes[v].pred;
        path.push_front(v);
    }

    std::string first_stop;
    std::string second_stop;
    std::string last_stop;
    std::string penultima_stop;

    auto b_it = path.begin();
    auto e_it = path.rbegin();

    int distance = nodes[dest].dist == INF ? -1 : nodes[dest].dist;
    
    first_stop = stops_and_lines.get_code_line(*b_it).first;
    b_it++;
    second_stop = stops_and_lines.get_code_line(*b_it).first;
    
    last_stop = stops_and_lines.get_code_line(*e_it).first;
    e_it++;
    penultima_stop = stops_and_lines.get_code_line(*e_it).first;

    if (first_stop == second_stop) path.pop_front();
    if (last_stop == penultima_stop) path.pop_back();

    return {std::make_pair(distance, path)};
}


std::vector<LineNode> LineGraph::get_nodes() {
    return this->nodes;
}