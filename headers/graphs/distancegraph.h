#include "../../headers/stops.h"
#include "../../headers/lines.h"
#include <list>

struct DistanceEdge {
    std::string line;
    double weight;
    int dest;
};

struct DistanceNode {
    std::list<DistanceEdge> adj;
    std::string line_used;
    double distance_available;
    bool visited;
    int pred;
    double dist;
};

class DistanceGraph {
private:
    double distance; //max distance the user chose to walk

    int n; //number of nodes

    std::vector<DistanceNode> nodes;

    void connect_nearby_stops(const Stops& stops, int curr_node_id, double distance);

    void build_graph(const Stops& stops, const Lines& lines, double distance);

    void add_edge(int src, int dest, double weight, std::string line);

    void dijkstra(int s);

public:
    DistanceGraph(const Stops& stops, const Lines& lines, int num, double distance);

    std::vector<DistanceNode> get_nodes();

    std::list<int> dijkstra_path(int src, int dest);
};