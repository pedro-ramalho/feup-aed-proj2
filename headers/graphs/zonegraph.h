#include "../../headers/stops.h"
#include "../../headers/lines.h"
#include <list>

struct ZoneEdge {
    std::string line;
    int dest;
    int weight;
};

struct ZoneNode {
    std::list<ZoneEdge> adj;
    std::string line_used;
    bool visited;
    double distance_available;
    int pred;
    int dist;
};

class ZoneGraph {
private:
    double distance; //max distance the user chose to walk

    int n; //number of nodes

    std::vector<ZoneNode> nodes;

    void connect_nearby_stops(const Stops& stops, int curr_node_id, double distance);

    void build_graph(const Stops& stops, const Lines& lines, double distance);

    void add_edge(int src, int dest, int weight, std::string line);

    void dijkstra(int s);

public:
    ZoneGraph(const Stops& stops, const Lines& lines, int num, double distance);

    std::vector<ZoneNode> get_nodes();

    std::list<int> dijkstra_path(const Stops& stops, int src, int dest);
};