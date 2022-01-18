#include "../headers/utils.h"

void clear_screen() { 
    std::cout << std::string(500, '\n') << std::endl; 
}

std::vector<std::string> read_file(std::string filename) {
    filename = "dataset/" + filename;
    std::vector<std::string> lines = std::vector<std::string>();
    std::string line = std::string();
    std::ifstream file(filename);

    if (!file.is_open()) std::cout << "Couldn't open file!" << std::endl;

    while (getline(file, line)) {
        lines.push_back(line);
        std::cout << line << '\n';
    }

    file.close();
    return lines;
}