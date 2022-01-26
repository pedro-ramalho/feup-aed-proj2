#include "../../headers/graphs/distancegraph.h"

DistanceGraph::DistanceGraph(const Stops& stops, const Lines& lines, int num, double distance) : nodes(num) {
    this->n = num;
    this->distance = distance;
    this->build_graph(stops, lines, distance);
}


void DistanceGraph::connect_nearby_stops(const Stops& stops, int curr_node_id, double distance) {

}

void DistanceGraph::build_graph(const Stops& stops, const Lines& lines, double distance) {
    std::string curr_line;
    std::pair<double, double> src_coords, dest_coords;

    int src_stop_id, dest_stop_id;
    double dist;

    for (const std::string path : lines.get_line_paths()) {
        std::vector<std::string> codes = lines.get_line_stops(path);
        std::string curr_line;

        for (int i = 1; i < codes.size() - 1; i++) {
            int src_stop_id = stops.get_id(codes[i - 1]);
            int dest_stop_id = stops.get_id(codes[i]);

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


void DistanceGraph::dijkstra(int s) {

}


std::list<int> DistanceGraph::dijkstra_path(const Stops& stops, int src, int dest) {

}


std::vector<DistanceNode> DistanceGraph::get_nodes() {
    return this->nodes;
}