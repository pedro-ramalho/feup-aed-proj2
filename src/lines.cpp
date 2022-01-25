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
}

void Lines::connect_nearby_stops(Graph& graph, double distance) {
    int size = graph.get_nodes().size();

    for (int i = 1; i < size - 1; i++)  
        for (int j = i + 1; j < size; j++) {                
            if (haversine(stops.get_coords(i), stops.get_coords(j)) <= distance) {
                graph.add_edge(i, j, 0, "A pe");
                graph.add_edge(j, i, 0, "A pe");
            }
        }
}

std::vector<std::string> Lines::get_line_paths() {
    return this->line_paths;
}

std::vector<std::string> Lines::get_line_stops(std::string path) {
    std::vector<std::string> stops = std::vector<std::string>();
    std::ifstream data;
    std::string line;

    data.open(path);
    std::getline(data, line); //ignores the first line

    while (std::getline(data, line)) stops.push_back(line);

    data.close();

    return stops;
}

Graph Lines::get_stops_graph(double distance) {
    Graph stops_graph(2487, true);
    std::string curr_line;

    std::cout << "Entrei no get_stops_graph()" << std::endl;

    for (const std::string path : this->line_paths) {
        if (path == "dataset/line_300_1.csv" || 
            path == "dataset/line_301_1.csv" || 
            path == "dataset/line_302_1.csv" || 
            path == "dataset/line_303_1.csv")
            continue;
    
        std::vector<std::string> codes = get_line_stops(path);

        for (int i = 1; i < codes.size() - 1; i++) {

            int src_stop_id = this->stops.get_id(codes[i - 1]);
            int dest_stop_id = this->stops.get_id(codes[i]);
            curr_line = path.substr(8, path.size() - 12);
             
            stops_graph.add_edge(src_stop_id, dest_stop_id, 1, curr_line);
        }
    }
    this->connect_nearby_stops(stops_graph, distance);

    return stops_graph;
}

Graph Lines::get_distances_graph(double distance) {
    Graph distances_graph(2487, true);

    for (const std::string path : this->line_paths) {
        std::vector<std::string> codes = get_line_stops(path);
        std::string curr_line;

        for (int i = 1; i < codes.size() - 1; i++) {
            int src_stop_id = this->stops.get_id(codes[i - 1]);
            int dest_stop_id = this->stops.get_id(codes[i]);

            std::pair<double, double> src_coords = stops.get_coords(src_stop_id);
            std::pair<double, double>  dest_coords = stops.get_coords(dest_stop_id);
            double distance = haversine(src_coords, dest_coords);
            curr_line = path.substr(8, path.size() - 12); 

            distances_graph.add_edge(src_stop_id, dest_stop_id, distance, curr_line);
        }
    }

    this->connect_nearby_stops(distances_graph, distance);

    return distances_graph;
}


Graph Lines::get_zones_graph(double distance) {
    Graph zones_graph(2487, true);

    for (const std::string path : this->line_paths) {
        std::vector<std::string> codes = get_line_stops(path);
        std::string curr_line;
        
        for (int i = 1; i < codes.size() - 1; i++) {
            int src_stop_id = this->stops.get_id(codes[i - 1]);
            int dest_stop_id = this->stops.get_id(codes[i]);
            
            std::string src_zone = stops.get_name_zone(src_stop_id).second;
            std::string dest_zone = stops.get_name_zone(dest_stop_id).second;

            int cost = src_zone == dest_zone ? 1 : 0;

            curr_line = path.substr(8, path.size() - 12); 
            zones_graph.add_edge(src_stop_id, dest_stop_id, cost, curr_line);
        }
    }
    this->connect_nearby_stops(zones_graph, distance);

    return zones_graph;
}