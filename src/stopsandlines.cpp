#include "../headers/stopsandlines.h"

StopsAndLines::StopsAndLines() {
    this->line_paths = lines.get_line_paths();
    this->read_stops_and_lines();
}

void StopsAndLines::read_stops_and_lines() {
    std::ifstream file;
    std::string word;
    std::string curr_line;
    int id = 1;

    for (const std::string path : this->line_paths) {
        file.open(path);
        std::getline(file, word); //ignores the first line
        curr_line = path.substr(8, path.size() - 12); 

        while (std::getline(file, word)) {
            std::pair<double, double> cords = stops.get_coords(stops.get_id(word));
            stopscode_line_to_id.insert({std::make_pair(word, curr_line), id});
            
            id_to_coords.insert({id, cords});
            id_to_line.insert({id, curr_line});
            id++;
        }
        file.close();
    }
}

std::vector<std::string> StopsAndLines::get_line_paths() const {
    return this->line_paths;
}

int StopsAndLines::get_stop_line_id(std::string code, std::string line) const {
    return stopscode_line_to_id.at(std::make_pair(code, line));
}

std::string StopsAndLines::get_line(int id) const {
    return id_to_line.at(id);
}

std::pair<double, double> StopsAndLines::get_coords(int id) const {
    return id_to_coords.at(id);
}

// LineGraph StopsAndLines::get_lines_graph(double distance) {
//     LineGraph lines_graph(5262, true);
//     std::ifstream file;
//     std::string word1;
//     std::string word2;
//     std::string curr_line;

//     for (const std::string path : this->line_paths) {
//         curr_line = path.substr(8, path.size() - 12); 
//         file.open(path);
    
//         std::getline(file, word1); //gets the number of lines
//         int num_stops = std::stoi(word1);
//         if (num_stops == 0) continue;
//         std::getline(file, word1);
//         while (std::getline(file, word2)) {
//             int src = stopscode_line_to_id[std::make_pair(word1, curr_line)];
//             int dest = stopscode_line_to_id[std::make_pair(word2, curr_line)];
//             lines_graph.add_edge(src, dest , 0);
//             word1 = word2;
//         }
        
//         file.close();
//     }

//     this->connect_nearby_stops(lines_graph, distance);

//     return lines_graph;
// }

// void StopsAndLines::connect_nearby_stops(LineGraph& graph, double distance) {
//     for (int i = 1; i < graph.get_nodes().size(); i++) 
//         for (int j = 1; j < graph.get_nodes().size(); j++) {
//             std::list<LEdge> edges = graph.get_nodes()[i].adj;
            
//             if (i != j && haversine(stops.get_coords(i), stops.get_coords(j)) <= distance)
//                 id_to_line[i].substr(0, id_to_line[i].size() - 2) == id_to_line[j].substr(0, id_to_line[j].size() - 2) ?  graph.add_edge(i, j, 0) : graph.add_edge(i, j, 1);
//         }
// }