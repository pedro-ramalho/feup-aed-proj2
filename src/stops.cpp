#include "../headers/stops.h"

Stops::Stops() {
    this->read_stops_file();
}

// Code,Name,Zone,Latitude,Longitude
void Stops::read_stops_file() {
    int id = 1;

    std::vector<std::string> values = std::vector<std::string>();
    std::ifstream data(STOPS_FILE);
    std::string line;

    std::getline(data, line); 

    while (std::getline(data, line)) {
        std::istringstream iss(line);
        std::string word;
        
        while (std::getline(iss, word, ',')) values.push_back(word);

        code_id.insert({values.at(0), id});
        id_to_code.insert({id, values.at(0)});

        code_to_zone.insert({values.at(0), values.at(2)});
        code_to_name.insert({values.at(0), values.at(1)});
        
        id_name_zone.insert({id, std::make_pair(values.at(1), values.at(2))});
        id_coords.insert({id, std::make_pair(std::stod(values.at(3)), std::stod(values.at(4)))});

        id++;
        values.clear();
    }
}

int Stops::get_id(std::string code) const {
    return code_id.at(code);
}

void Stops::add_stop(std::string code, int id, std::string name, std::string zone, std::pair<double, double> coords) {
    code_id.insert({code, id});
    id_to_code.insert({id, code});

    code_to_zone.insert({code, zone});
    code_to_name.insert({code, name});
        
    id_name_zone.insert({id, std::make_pair(name, zone)});
    id_coords.insert({id, coords});
}

std::string Stops::get_name(std::string code) const {
    return code_to_name.at(code);
}

std::string Stops::get_zone(std::string code) const {
    return code_to_zone.at(code);
}

std::string Stops::get_code(int id) const {
    return id_to_code.at(id);
}

std::pair<std::string, std::string> Stops::get_name_zone(int id) const {
    return id_name_zone.at(id);
}

std::pair<double, double> Stops::get_coords(int id) const {
    return id_coords.at(id);
}