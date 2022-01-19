#include <iostream>
#include "headers/utils.h"
#include "headers/graph.h"

int main() {
    //creates an undirected graph with 9 nodes
    Graph g(9, false);
    g.add_edge(1,2);
    g.add_edge(1,3);
    g.add_edge(2,4);
    g.add_edge(3,4);
    g.add_edge(4,5);
    g.add_edge(5,6);
    g.add_edge(5,7);
    g.add_edge(6,9);
    g.add_edge(7,8);

    return 0;
}