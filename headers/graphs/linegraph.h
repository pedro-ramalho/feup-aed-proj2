#pragma once

#include <list>
#include <vector>
#include <string>
#include <climits>
#include "../../headers/minheap.h"

#define INF (INT_MAX/2)

struct LEdge {
    int dest; //destination node
    int weight; //integer weight (can change type if needed)
};

struct LNode {
    std::list<LEdge> adj; //list of outgoing edges (to adjacent nodes)
    std::string line;
    bool visited; //true if the node has been visited during a search
    int dist; //distance between this current Node and another Node
    int pred;
};

class LineGraph {
private:
    int n; //number of nodes

    bool has_dir; //true if the graph is directed

    std::vector<LNode> nodes; //stores each node of the graph
public:
    //num of nodes and dir
    LineGraph(int nodes, bool has_dir);
    
    void add_edge(int src, int dest, int weight);

    std::vector<LNode> get_nodes() {return this->nodes;}

    void dijkstra(int s);

    std::list<int> dijkstra_path(int a, int b);

    int dijkstra_distance(int a, int b);
};