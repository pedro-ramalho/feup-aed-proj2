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

    std::vector<std::string> line_paths;

    Lines lines;

    Stops stops;
public:
    StopsAndLines();

    void read_stops_and_lines();

    void connect_nearby_stops(LineGraph& graph, double distance);

    LineGraph get_lines_graph(double distance);
};