#pragma once

#include <map>
#include <fstream>
#include <algorithm>
#include "../headers/lines.h"

class StopsAndLines {
private:
    std::map<std::pair<std::string, std::string>, int> stopscode_line_to_id;

    std::map<int, std::string> id_to_line;

    std::map<int, std::pair<double, double>> id_to_coords;

    std::map<int, std::pair<std::string, std::string>> id_to_code_line;

    std::map<int, std::string> id_to_zone;

    std::vector<std::string> line_paths;

    Lines lines;

    Stops stops;

    void read_stops_and_lines();

public:
    StopsAndLines();

    std::vector<std::string> get_line_paths() const;

    std::pair<double, double> get_coords(int id) const;

    std::string get_line(int id) const;

    std::string get_zone(int id) const;

    std::pair<std::string, std::string> get_code_line(int id) const;

    std::vector<std::string> get_codes(std::string path) const;

    int get_stop_line_id(std::string code, std::string line) const;
};