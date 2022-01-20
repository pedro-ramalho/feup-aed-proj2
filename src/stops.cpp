#include "../headers/stops.h"

Stops::Stops() {
    this->read_stops_file();
}

void Stops::read_stops_file() {
    int id = 1;

    std::vector<std::string> values = std::vector<std::string>();
    std::ifstream data(STOPS_FILE);
    std::string line;

    std::getline(data, line); //ignore first line

    while (std::getline(data, line)) {
        std::istringstream iss(line);
        std::string word;
        
        while (std::getline(iss, word, ',')) values.push_back(word);

        code_id.insert({values.at(0), id});
        id_name.insert({id, std::make_pair(values.at(1), values.at(2))});
        id_coords.insert({id, std::make_pair(std::stod(values.at(3)), std::stod(values.at(4)))});

        id++;
        values.clear();
    }
}

int Stops::get_id(std::string stop) {
    return code_id[stop];
}

std::pair<std::string, std::string> Stops::get_name(int id) {
    return id_name[id];
}

std::pair<double, double> Stops::get_coords(int id) {
    return id_coords[id];
}