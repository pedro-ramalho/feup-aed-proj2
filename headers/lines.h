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

    /**
     * @brief A vector containing the strings correspondent to the existing lines
     */
    std::vector<std::string> line_paths;

    /**
     * @brief The relative path to the lines file
     */
    const std::string LINES_FILE = "dataset/lines.csv";
    
    /**
     * @brief The prefix to a line in the .csv file
     */
    const std::string LINE_PREFIX = "dataset/line_";

    /**
     * @brief Reads the lines file and pushes back the lines to the line_paths vector
     */
    void read_lines_file();

public:

    /**
     * @brief Construct a new Lines object
     */
    Lines();

    /**
     * @brief Get the line paths
     * @return the vector containing the lines
     */
    std::vector<std::string> get_line_paths() const;

    /**
     * @brief Get the stops in a line
     * @param path a line's path
     * @return a vector containing the codes of the stops in the path
     */
    std::vector<std::string> get_line_stops(std::string path) const;

};