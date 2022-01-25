#pragma once

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <climits>
#include "../headers/minheap.h"

#define INF (INT_MAX/2)

//---------------------------------------------//
//  This simplified Graph class was made by    //
//  Professor Pedro Ribeiro and most methods   //
//  were reused from Practical Classes         //
//---------------------------------------------//

struct Edge {
    int dest; //destination node
    double weight; //integer weight (can change type if needed)
    std::string line;
};

struct Node {
    std::list<Edge> adj; //list of outgoing edges (to adjacent nodes)
    bool visited; //true if the node has been visited during a search
    int dist; //distance between this current Node and another Node
    int pred;
};

class Graph {
private:

    int n; // graph size (vertices are numbered from 1 to n)
    bool has_dir; //true if the grap is directed
    std::vector<Node> nodes; //vector of nodes being represented

public:
    //constructor: num of nodes and undirected (default)
    Graph(int nodes, bool has_dir);

    //add edge from source to destination with a certain weight
    void add_edge(int src, int dest, double weight, std::string line);

    //depth-first search
    void dfs(int v);

    //depth-first search but returns the number of nodes connected to node v
    int dfs_counter(int  v);

    //depth-first search but returns a possible topological order for the nodes
    void dfs_topological(int v, std::list<int>& order);

    //breadth-first search
    void bfs(int v);

    std::list<int> bfs_path(int a, int b);

    //breadth-first search but returns the distance between nodes a and b
    int bfs_distances(int a, int b);

    //other functions (I put them here because they might be useful in the future)
    int out_degree(int v);
    
    int connected_components();

    int giant_component();
    
    int distance(int a, int b);

    std::list<int> topological_sorting();

    std::vector<Node> get_nodes() { return this->nodes; }
    //prim algorithm

    //kruskal algorithm

    //dijkstra algorithm

    void dijkstra(int s);

    std::list<int> dijkstra_path(int a, int b);

    int dijkstra_distance(int a, int b);
    
};