#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Lines {
private:
    std::vector<std::string> line_paths;
    const std::string LINES_FILE = "dataset/lines.csv";
    const std::string LINE_PREFIX = "dataset/line_";

    void read_lines_file();
public:
    Lines();

    void build_graph();
};