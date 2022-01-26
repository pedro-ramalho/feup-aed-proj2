#include "../../headers/graphs/zonegraph.h"
#include "../../headers/stops.h"
#include "../../headers/lines.h"

ZoneGraph::ZoneGraph(const Stops& stops, const Lines& lines, int num, double distance) : nodes(num) {
    this->n = num;
    this->distance = distance;
    this->build_graph(stops, lines, distance);
}


void ZoneGraph::connect_nearby_stops(const Stops& stops, int curr_node_id, double distance) {

}


void ZoneGraph::build_graph(const Stops& stops, const Lines& lines, double distance) {
    std::string curr_line, src_zone, dest_zone;
    int src_stop_id, dest_stop_id, cost;

    for (std::string path : lines.get_line_paths()) {
        std::vector<std::string> codes = lines.get_line_stops(path);

        if (codes.empty()) continue;

        for (int i = 1; i < codes.size(); i++) {
            src_stop_id = stops.get_id(codes[i - 1]);
            dest_stop_id = stops.get_id(codes[i]);

            src_zone = stops.get_name_zone(src_stop_id).second;
            dest_zone = stops.get_name_zone(dest_stop_id).second;

            cost = src_zone == dest_zone ? 1 : 0;

            curr_line = path.substr(8, path.size() - 12);
            this->add_edge(src_stop_id, dest_stop_id, cost, curr_line);
        }
    }
}


void ZoneGraph::add_edge(int src, int dest, int weight, std::string line) {
    if (src < 1 || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({line, dest, weight});
}


void ZoneGraph::dijkstra(int s) {

}


std::list<int> ZoneGraph::dijkstra_path(const Stops& stops, int src, int dest) {

}


std::vector<ZoneNode> ZoneGraph::get_nodes() {
    return this->nodes;
}