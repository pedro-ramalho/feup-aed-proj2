#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>
#include <cmath>
#include <map>
#include <sstream>

class Stops {
private:
    std::map<std::string, int> code_id;

    std::map<int, std::pair<std::string, std::string>> id_name_zone;

    std::map<int, std::pair<double, double>> id_coords;

    const std::string STOPS_FILE = "dataset/stops.csv";

    void read_stops_file();
public:
    Stops();

    int get_id(std::string code);

    std::pair<std::string, std::string> get_name_zone(int id);

    std::pair<double, double> get_coords(int id);
};
