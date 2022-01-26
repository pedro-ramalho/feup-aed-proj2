#include "../headers/stops.h"
#include "../headers/lines.h"
#include <list>

struct StopEdge {
    std::string line;
    int dest; //destination node
    int weight; //default = 1
};

struct StopNode {
    std::list<StopEdge> adj;
    std::string line_used;
    bool visited;
    int pred;
    double distance_available;
};

class StopGraph {
private:
    double distance;

    int n; //number of nodes

    std::vector<StopNode> nodes;

    void connect_nearby_stops(const Stops& stops, double distance);

    void new_connect_nearby_stops(const Stops& stops, int curr_node_id, double distance);

    void build_graph(const Stops& stops, const Lines& lines, double distance);

public:
    StopGraph(const Stops& stops, const Lines& lines, int num, double distance);

    void add_edge(int src, int dest, int weight, std::string line);

    std::list<int> bfs_path(const Stops& stops, int src, int dest);

    std::vector<StopNode> get_nodes();
};