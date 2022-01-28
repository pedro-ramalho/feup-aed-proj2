#include "../../headers/graphs/stopgraph.h"
#include "../../headers/stops.h"
#include "../../headers/lines.h"

StopGraph::StopGraph(const Stops& stops, const Lines& lines, int num, double distance) : nodes(num + 1) {
    this->n = num;
    this->distance = distance;
    this->build_graph(stops, lines, distance);
}

void StopGraph::connect_nearby_stops(const Stops& stops, int curr_node_id, double distance) {
    int size = this->nodes.size();

    for (int j = 1; j < size; j++)                
        if (curr_node_id != j && haversine(stops.get_coords(curr_node_id), stops.get_coords(j)) <= distance) {
            this->add_edge(curr_node_id, j, 1, "A pé"); 
        }
}

void StopGraph::build_graph(const Stops& stops, const Lines& lines, double distance) {
    std::string curr_line;

    for (std::string path : lines.get_line_paths()) {
        std::vector<std::string> codes = lines.get_line_stops(path);

        if (codes.empty()) continue;

        for (int i = 1; i < codes.size(); i++) {
            int src_stop_id = stops.get_id(codes[i - 1]);
            int dest_stop_id = stops.get_id(codes[i]);
            curr_line = path.substr(8, path.size() - 12);
            this->add_edge(src_stop_id, dest_stop_id, 1, curr_line);
        }
    }
}

void StopGraph::add_edge(int src, int dest, int weight, std::string line) {
    if (src < 1 || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({line, dest, weight});
}

std::list<int> StopGraph::bfs_path(const Stops& stops, int a, int b) {
    for (int i = 1; i < this->n; i++) nodes[i].visited = false;

    std::queue<int> q = std::queue<int>();
    std::list<int> path = std::list<int>();

    this->nodes[a].visited = true;
    this->nodes[a].pred = a;
    this->nodes[a].distance_available = this->distance;
    this->nodes[a].line_used = "Início";
    q.push(a);

    while (!q.empty()) {
        int u = q.front();
        this->connect_nearby_stops(stops, u, nodes[u].distance_available);
        q.pop();
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            if (!nodes[v].visited) {
                nodes[v].pred = u;
                nodes[v].line_used = e.line;
                nodes[v].visited = true;
                nodes[v].distance_available = e.line == "A pé" ? nodes[u].distance_available - haversine(stops.get_coords(u), stops.get_coords(v)) : nodes[u].distance_available;
                q.push(v);
            }
        }
    }

    int i = b;
    while (nodes[i].pred != i) {
        path.push_front(i);
        i = nodes[i].pred;
    }

    path.push_front(i);
    return path;
}

std::vector<StopNode> StopGraph::get_nodes() {
    return this->nodes;
}