#include "../../headers/stops.h"
#include "../../headers/lines.h"
#include <list>


struct StopEdge {
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

struct StopNode {
    /**
     * @brief List of edges connected to the node
     */
    std::list<StopEdge> adj;

    /**
     * @brief The line used in the path
     */
    std::string line_used;

    /**
     * @brief Boolean dictating whether the node has been visited or not
     */
    bool visited;

    /**
     * @brief Predecessor of this Node
     */
    int pred;

    /**
     * @brief Distance available to walk 
     */
    double distance_available;
};


class StopGraph {
private:
    /**
     * @brief Walking distance input by the user
     */
    double distance; 

    /**
     * @brief Number of nodes in the Graph
     */
    int n;

    /**
     * @brief Container of each node
     */
    std::vector<StopNode> nodes;

    /**
     * @brief Method that connects a stop to all of the nearby stops, if they are within a certain distance
     * 
     * @param stops all the existing stops
     * @param curr_node_id the ID of the current stop
     * @param distance the max distance to which you can connect a stop to the current one
     */
    void connect_nearby_stops(const Stops& stops, int curr_node_id, double distance);

    /**
     * @brief Builds the Graph itself
     * @param stops data class storing all stops
     * @param lines data class storing all lines
     * @param distance walking distance input by the user
     */
    void build_graph(const Stops& stops, const Lines& lines, double distance);

public:
    /**
     * @brief Construct a new Stop Graph object
     * @param stops data class storing all stops
     * @param lines data class storing all lines
     * @param num number of nodes
     * @param distance walking distance input by the user
     */
    StopGraph(const Stops& stops, const Lines& lines, int num, double distance);

    /**
     * @brief Adds and edge connecting Node src and dest
     * @param src source node
     * @param dest destination node
     * @param weight weight of the node
     * @param line line used in the path
     */
    void add_edge(int src, int dest, int weight, std::string line);

    /**
     * @brief Calculates the best path using Breadth-First-Search between Nodes src and dest
     * @param stops data class storing all stops
     * @param src source node
     * @param dest destination node
     * @return best path available
     */
    std::list<int> bfs_path(const Stops& stops, int src, int dest);

    /**
     * @brief Get the vector of nodes
     * @return std::vector<StopNode> 
     */
    std::vector<StopNode> get_nodes();
};