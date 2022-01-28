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
            std::pair<double, double> coords = stops.get_coords(stops.get_id(word));
            stopscode_line_to_id.insert({std::make_pair(word, curr_line), id});
            
            id_to_coords.insert({id, coords});
            id_to_line.insert({id, curr_line});
            id_to_code_line.insert({id, std::make_pair(word, curr_line)});
            id++;
        }
        file.close();
    }
}

std::string StopsAndLines::get_zone(int id) const {
    return id_to_zone.at(id);
}

std::vector<std::string> StopsAndLines::get_codes(std::string path) const {
    return lines.get_line_stops(path);
}

std::pair<std::string, std::string> StopsAndLines::get_code_line(int id) const {
    return id_to_code_line.at(id);
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

void StopsAndLines::add_stop_and_line(std::string code, int id, std::string name, std::string zone, std::pair<double, double> coords, std::string line) {
    stopscode_line_to_id.insert({std::make_pair(code, line), id});
    id_to_coords.insert({id, coords});
    id_to_line.insert({id, line});
    id_to_code_line.insert({id, std::make_pair(code, line)});

}
