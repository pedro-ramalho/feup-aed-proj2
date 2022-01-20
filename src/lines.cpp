#include "../headers/lines.h"

Lines::Lines() {
    this->read_lines_file();
}

void Lines::read_lines_file() {
    std::ifstream data(LINES_FILE);
    std::string line;

    std::getline(data, line); //ignores first line

    while (std::getline(data, line)) {
        std::istringstream iss(line);
        std::string word;

        std::getline(iss, word, ',');
        word = LINE_PREFIX + word;

        line_paths.push_back(word + "_0.csv");
        line_paths.push_back(word + "_1.csv");
    }

    std::cout << this->line_paths.size() << std::endl;
}

std::vector<std::string> Lines::build_graph(std::string path) {
    std::vector<std::string> stops = std::vector<std::string>();
    std::ifstream data;
    std::string line;

    data.open(path);
    std::getline(data, line); //ignores the first line

    while (std::getline(data, line)) stops.push_back(line);

    data.close();

    return stops;
}

Graph Lines::get_stops_graph() {
    Graph stops_graph(2487, true);

    for (const std::string path : this->line_paths) {
        std::vector<std::string> codes = build_graph(path);
        for (int i = 1; i < this->line_paths.size() - 1; i++) {
            int src_stop_id = this->stops.get_id(codes[i - 1]);
            int dest_stop_id = this->stops.get_id(codes[i]);
            stops_graph.add_edge(src_stop_id, dest_stop_id, 1);
        }
    }

    return stops_graph;
}

Graph Lines::get_distances_graph() {

}

Graph Lines::get_lines_graph() {

}

Graph Lines::get_zones_graph() {
    
}