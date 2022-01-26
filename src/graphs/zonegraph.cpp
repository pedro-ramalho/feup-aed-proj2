#include "../../headers/graphs/zonegraph.h"
#include "../../headers/stops.h"
#include "../../headers/lines.h"

ZoneGraph::ZoneGraph(const Stops& stops, const Lines& lines, int num, double distance) : n(num), nodes(num + 1) {
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


//dijkstra original - tem de se mudar para o pretendido
void ZoneGraph::dijkstra(int s) {
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
std::list<int> ZoneGraph::dijkstra_path(const Stops& stops, int src, int dest) {
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


std::vector<ZoneNode> ZoneGraph::get_nodes() {
    return this->nodes;
}