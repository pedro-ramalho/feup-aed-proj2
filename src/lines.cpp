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

        line_paths.push_back(word + "_0.csv");
        line_paths.push_back(word + "_1.csv");
    }

    std::cout << this->line_paths.size() << std::endl;
}

void Lines::build_graph() {
    std::ifstream data;
    std::string line;
    int counter = 0;

    for (const std::string path : this->line_paths) {
        std::cout << "Path: " << path << std::endl;
        data.open(path);
        std::getline(data, line); //ignores first line of each file
        
        while (std::getline(data, line)) std::cout << line << " ";
        std::cout << '\n';
        std::cout << '\n';
        data.close();
    }
}