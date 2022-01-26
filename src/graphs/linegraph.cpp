#include "../../headers/graphs/linegraph.h"

LineGraph::LineGraph(const StopsAndLines& stops_and_lines, int num, double distance) : nodes(num) {
    this->n = num;
    this->distance = distance;
    this->build_graph(stops_and_lines, distance);
}


void LineGraph::connect_nearby_stops(const StopsAndLines& stops_and_lines, int curr_node_id, double distance) {

}

void LineGraph::build_graph(const StopsAndLines& stops_and_lines, double distance) {
    std::ifstream file;
    std::string word1;
    std::string word2;
    std::string curr_line;

    for (const std::string path : stops_and_lines.get_line_paths()) {
        curr_line = path.substr(8, path.size() - 12); 
        file.open(path);
    
        std::getline(file, word1); //gets the number of lines
        int num_stops = std::stoi(word1);
        if (num_stops == 0) continue;

        std::getline(file, word1);

        while (std::getline(file, word2)) {
            int src = stops_and_lines.get_stop_line_id(word1, curr_line);
            int dest = stops_and_lines.get_stop_line_id(word2, curr_line);
            this->add_edge(src, dest , 0, curr_line);
            word1 = word2;
        }
        
        file.close();
    }

}

void LineGraph::add_edge(int src, int dest, int weight, std::string line) {
    if (src < 1 || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({line, dest, weight});
}

void LineGraph::dijkstra(int s) {

}

std::vector<LineNode> LineGraph::get_nodes() {
    return this->nodes;
}

std::list<int> LineGraph::dijkstra_path(const StopsAndLines& stops_and_lines, int src, int dest) {

}