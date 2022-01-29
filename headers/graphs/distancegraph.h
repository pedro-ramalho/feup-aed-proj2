#include "../stops.h"
#include "../lines.h"

#include <list>

struct DistanceEdge {

    /**
     * @brief Line connecting two stops
     * 
     */
    std::string line;

    /**
     * @brief Distance between the stops connected by the edge
     * 
     */
    double weight;

    /**
     * @brief Destination node
     * 
     */
    int dest;
};

struct DistanceNode {

    /**
     * @brief List of edges connecting current node to others
     * 
     */
    std::list<DistanceEdge> adj;

    /**
     * @brief Line used in the path
     * 
     */
    std::string line_used;

    /**
     * @brief The distance a user is willing to walk when at the current node
     * 
     */
    double distance_available;

    /**
     * @brief Boolean dictating whether or not the node has been visited
     * 
     */
    bool visited;

    /**
     * @brief Previous node to the current node
     * 
     */
    int pred;

    /**
     * @brief 
     * 
     */
    double dist;
};

class DistanceGraph {
private:

    /**
     * @brief Max distance the user chose to walk
     * 
     */
    double distance;

    /**
     * @brief Number of nodes in the graph
     * 
     */
    int n;

    /**
     * @brief The vector containing the graph's nodes
     * 
     */
    std::vector<DistanceNode> nodes;

    /**
     * @brief Method that connects a stop to all of the nearby stops, if they are within a certain distance
     * 
     * @param stops all the existing stops
     * @param curr_node_id the ID of the current stop
     * @param distance the max distance to which you can connect a stop to the current one
     */
    void connect_nearby_stops(const Stops& stops, int curr_node_id, double distance);

    /**
     * @brief Builds the graph
     * 
     * @param stops all the existing stops
     * @param lines all the existing lines
     * @param distance the max distance to which you can connect a stop to the current one
     */
    void build_graph(const Stops& stops, const Lines& lines, double distance);

    /**
     * @brief Calculates the best path to every node from the given starting node
     * 
     * @param stops all the existing stops
     * @param s the starting node
     */
    void dijkstra(const Stops& stops, int s);

public:
    
    /**
     * @brief Construct a new Distance Graph object
     * 
     * @param stops all the existing stops
     * @param lines all the existing lines
     * @param num the number of notes in the graph
     * @param distance the max distance to which you can connect a stop to the current one
     */
    DistanceGraph(const Stops& stops, const Lines& lines, int num, double distance);

    /**
     * @brief Add an edge to a node
     * 
     * @param src the starting node
     * @param dest the destination node
     * @param weight the weight of the edge
     * @param line the line the edge is a fragment of
     */
    void add_edge(int src, int dest, double weight, std::string line);

    /**
     * @brief Get the nodes object
     * 
     * @return the vector of nodes in the graph
     */
    std::vector<DistanceNode> get_nodes();

    /**
     * @brief 
     * 
     * @param stops all the existing nodes
     * @param src the starting node
     * @param dest the destination node
     * @return a pair containing the distance travelled and the path
     */
    std::pair<double, std::list<int>> dijkstra_distance_path(const Stops& stops, int src, int dest);
};