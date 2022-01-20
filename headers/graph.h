#pragma once

#include <vector>
#include <list>
#include <queue>
#include <iostream>

//---------------------------------------------//
//  This simplified Graph class was made by    //
//  Professor Pedro Ribeiro and most methods   //
//  were reused from Practical Classes         //
//---------------------------------------------//

class Graph {
private:
    struct Edge {
        int dest; //destination node
        int weight; //integer weight (can change type if needed)
    };

    struct Node {
        std::list<Edge> adj; //list of outgoing edges (to adjacent nodes)
        bool visited; //true if the node has been visited during a search
        int distance; //distance between this current Node and another Node
    };

    int n; // graph size (vertices are numbered from 1 to n)
    bool has_dir; //true if the grap is directed
    std::vector<Node> nodes; //vector of nodes being represented

public:
    //constructor: num of nodes and undirected (default)
    Graph(int nodes, bool has_dir);

    //add edge from source to destination with a certain weight
    void add_edge(int src, int dest, int weight = 1);

    //depth-first search
    void dfs(int v);

    //depth-first search but returns the number of nodes connected to node v
    int dfs_counter(int  v);

    //depth-first search but returns a possible topological order for the nodes
    void dfs_topological(int v, std::list<int>& order);

    //breadth-first search
    void bfs(int v);

    //breadth-first search but returns the distance between nodes a and b
    int bfs_distances(int a, int b);

    //other functions (I put them here because they might be useful in the future)
    int out_degree(int v);
    
    int connected_components();

    int giant_component();
    
    int distance(int a, int b);

    std::list<int> topological_sorting();

    //prim algorithm

    //kruskal algorithm

    //dijkstra algorithm
};