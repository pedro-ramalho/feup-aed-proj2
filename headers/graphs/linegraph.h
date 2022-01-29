#pragma once

#include <list>
#include <vector>
#include <string>
#include <climits>
#include "../../headers/minheap.h"
#include "../../headers/stopsandlines.h"

#define INF (INT_MAX/2)

struct LineEdge {
    /**
     * @brief Line connecting both Stops
     */
    std::string line;

    /**
     * @brief Destination node
     */
    int dest;
    
    /**
     * @brief Weight of the edge
     */
    int weight;
};

struct LineNode {

    /**
     * @brief List of edges connected to the node
     * 
     */
    std::list<LineEdge> adj;

    /**
     * @brief The line used in the path
     * 
     */
    std::string line_used;

    /**
     * @brief Boolean dictating whether the node has been visited or not
     * 
     */
    bool visited;

    /**
     * @brief Distance the user is willing to walk when at the current node
     * 
     */
    double distance_available;

    /**
     * @brief The previous node to the current one
     * 
     */
    int pred;

    /**
     * @brief Distance between the source node and the current one
     * 
     */
    int dist;

    /**
     * @brief Boolean dictating whether the node has been connected to nearby stops; false as default
     * 
     */
    bool connected_nearby_stops = false;
};

class LineGraph {
private:
    /**
     * @brief Walking distance input by the user
     * 
     */
    double distance;
    
    /**
     * @brief Number of nodes in the Graph
     */
    int n;

    /**
     * @brief Container of each node
     */
    std::vector<LineNode> nodes;

    /**
     * @brief Connects the SOURCE and DEST Stops
     * @param stops_and_lines data class storing the pairs(stop, line)
     * @param curr_node_id source node
     */
    void connect_begin_and_end_stops(const StopsAndLines& stops_and_lines, int curr_node_id);

    /**
     * @brief Connects every Stop close to the current Node, if they're within a certain distance
     * @param stops_and_lines data class storing the pairs(stop, line)
     * @param curr_node_id source node
     * @param distance distance to connect the Stops
     */
    void connect_nearby_stops(const StopsAndLines& stops_and_lines, int curr_node_id, double distance);

    /**
     * @brief Builds the graph itself
     * @param stops_and_lines data class storing the pairs(stop, line)
     * @param distance distance to connect the Stops
     */
    void build_graph(const StopsAndLines& stops_and_lines, double distance);

    /**
     * @brief Adds a edge to Graph
     * @param src source node
     * @param dest destination node
     * @param weight weight of the edge
     * @param line line of the edge
     */
    void add_edge(int src, int dest, int weight, std::string line);

    /**
     * @brief Finds the best path between Node s (source) and d (destination)
     * @param stops_and_lines data class storing the pairs(stop, line)
     * @param s source node
     * @param d destination node
     */
    void dijkstra(const StopsAndLines& stops_and_lines, int s, int d);


public:
    /**
     * @brief Construct a new Line Graph object
     * @param stops_and_lines data class storing the pairs(stop, line)
     * @param num number of nodes
     * @param distance distance to connect the Stops
     */
    LineGraph(const StopsAndLines& stops_and_lines, int num, double distance);

    /**
     * @brief Get the vector of nodes object
     * @return std::vector<LineNode> 
     */
    std::vector<LineNode> get_nodes();

    /**
     * @brief Calculates the best path between Node src and dest
     * @param stops_and_lines data class storing the pairs(stop, line)
     * @param src source node
     * @param dest destination node
     * @return cost of the path, list of the nodes making up the path 
     */
    std::pair<int, std::list<int>> dijkstra_distance_path(const StopsAndLines& stops_and_lines, int src, int dest);
};