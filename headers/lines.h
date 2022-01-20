#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../headers/graph.h"
#include "../headers/stops.h"


class Lines {
private:
    std::vector<std::string> line_paths;
    Stops stops;

    const std::string LINES_FILE = "dataset/lines.csv";
    const std::string LINE_PREFIX = "dataset/line_";

    void read_lines_file();
public:
    Lines();

    std::vector<std::string> build_graph(std::string path);

    /*
     * A graph to be used when the user chooses the path with the least amount of Stops.
     * Making the weight of every edge equal to 1 should be enough to solve this problem.
     * Apply Dijkstra's algorithm and it should be done
    */
    Graph get_stops_graph();
    

    /*
    * A graph to be used when the user chooses the shortest path in terms of distance.
    * The weight of each edge should be equal to the distance between the two connecting nodes.
    * Apply Dijkstra's algorithm and it should be done
    */
    Graph get_distances_graph();


    /*
    * A graph to be used when the user chooses the path with the least amount of line switches.
    * Still need to figure out a way to do this one.
    */
    Graph get_lines_graph();


    /*
    * A graph to be used when the user chooses the cheapest (crosses the least amount of different zones) path.
    * Still need to figure out how to do this one.
    */
    Graph get_zones_graph();
};