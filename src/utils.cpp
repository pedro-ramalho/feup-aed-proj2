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

/*
    Haversine formula to calculate the distance (in km) between 2 points
    using their latitudes and longitudes.
    PS: I totally did not steal this code
*/

double haversine(double lat1, double lon1, double lat2, double lon2) {
    //distance between latitudes and longitudes
    double d_lat = (lat2 - lat1) * M_PI / 180;
    double d_lon = (lon2 - lon1) * M_PI / 180;

    //convert to radians
    lat1 = (lat1) * M_PI / 180;
    lat2 = (lat2) * M_PI / 180;

    //apply formula
    double a = pow(sin(d_lat/2), 2) +
               pow(sin(d_lon/2), 2) *
               cos(lat1) * cos(lat2);
    
    return 6371 * 2 * asin(sqrt(a));    
}