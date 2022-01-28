#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../headers/utils.h"
#include "../headers/graphs/graph.h"
#include "../headers/stops.h"

class Lines {
private:
    std::vector<std::string> line_paths;

    const std::string LINES_FILE = "dataset/lines.csv";
    const std::string LINE_PREFIX = "dataset/line_";

    void read_lines_file();

public:
    Lines();

    std::vector<std::string> get_line_paths() const;

    std::vector<std::string> get_line_stops(std::string path) const;

};