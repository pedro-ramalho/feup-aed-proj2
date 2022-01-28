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

        this->line_paths.push_back(word + "_0.csv");
        this->line_paths.push_back(word + "_1.csv");
    }
}


std::vector<std::string> Lines::get_line_stops(std::string path) const {
    std::vector<std::string> stops = std::vector<std::string>();
    std::ifstream data;
    std::string line;

    data.open(path);
    std::getline(data, line); //ignores the first line

    while (std::getline(data, line)) stops.push_back(line);

    data.close();

    return stops;
}


std::vector<std::string> Lines::get_line_paths() const {
    return this->line_paths;
}
