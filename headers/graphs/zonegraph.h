#include "../../headers/stops.h"
#include "../../headers/lines.h"
#include <list>

struct ZoneEdge {
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

struct ZoneNode {
    /**
     * @brief List of edges connected to the node
     */
    std::list<ZoneEdge> adj;

    /**
     * @brief The line used in the path
     */
    std::string line_used;

    /**
     * @brief Boolean dictating whether the node has been visited or not
     */
    bool visited;

    /**
     * @brief Distance available to walk 
     */
    double distance_available;

    /**
     * @brief Predecessor of this Node
     */
    int pred;

    /**
     * @brief Distance between the sourceNode and this Node
     */
    int dist;
};

class ZoneGraph {
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
    std::vector<ZoneNode> nodes;

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

    /**
     * @brief Finds the best path to each Node starting from Node s
     * @param stops all the existing nodes
     * @param s the starting node
     */
    void dijkstra(const Stops& stops, int s);

public:
    /**
     * @brief Construct a new Zone Graph object
     * @param stops data class storing all stops
     * @param lines data class storing all lines
     * @param num number of nodes
     * @param distance walking distance input by the user
     */
    ZoneGraph(const Stops& stops, const Lines& lines, int num, double distance);

    /**
     * @brief Get the vector of nodes
     * @return std::vector<ZoneNode> 
     */
    std::vector<ZoneNode> get_nodes();
    
    /**
     * @brief Calculates the best path between Node src and dest
     * @param stops_and_lines data class storing the pairs(stop, line)
     * @param src source node
     * @param dest destination node
     * @return cost of the path, list of the nodes making up the path 
     */
    std::pair<int, std::list<int>> dijkstra_distance_path(const Stops& stops, int src, int dest);

    /**
     * @brief Adds and edge connecting Node src and dest
     * @param src source node
     * @param dest destination node
     * @param weight weight of the node
     * @param line line used in the path
     */
    void add_edge(int src, int dest, int weight, std::string line);
};