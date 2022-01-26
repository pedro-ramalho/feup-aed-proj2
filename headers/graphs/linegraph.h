#pragma once

#include <list>
#include <vector>
#include <string>
#include <climits>
#include "../../headers/minheap.h"
#include "../../headers/stopsandlines.h"

#define INF (INT_MAX/2)

struct LineEdge {
    std::string line;
    int dest;
    int weight;
};

struct LineNode {
    std::list<LineEdge> adj;
    std::string line_used;
    bool visited;
    double distance_available;
    int pred;
};

class LineGraph {
private:
    double distance;

    int n;

    std::vector<LineNode> nodes;

    void connect_nearby_stops(const StopsAndLines& stops_and_lines, int curr_node_id, double distance);

    void build_graph(const StopsAndLines& stops_and_lines, double distance);

    void add_edge(int src, int dest, int weight, std::string line);

    void dijkstra(int s);

public:
    LineGraph(const StopsAndLines& stops_and_lines, int num, double distance);

    std::vector<LineNode> get_nodes();

    std::list<int> dijkstra_path(const StopsAndLines& stops_and_lines, int src, int dest);
};