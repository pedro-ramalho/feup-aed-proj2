#include "../headers/utils.h"

std::map<int, std::pair<std::string, std::string>> id_code;

std::map<int, std::string> id_zone;

std::map<int, std::pair<double, double>> id_coords;

void clear_screen() { 
    std::cout << std::string(500, '\n') << std::endl; 
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

std::pair<std::string, std::string> get_code(int id) {
    return id_code[id];
}

std::string get_zone(int id) {
    return id_zone[id];
}

std::pair<double, double> get_coords(int id) {
    return id_coords[id];
}

void read_stops_file() {
    std::ifstream data(STOPS_FILE);

    std::string str;
    std::getline(data, str);

    int id = 1;

    std::vector<std::string> values = std::vector<std::string>();

    while (std::getline(data, str)) { 
        std::istringstream iss(str);
        std::string token;
        while (std::getline(iss, token, ',')) {
            values.push_back(token);
        }

        id_code.insert({id, std::make_pair(values.at(0), values.at(1))});
        id_zone.insert({id, values.at(2)});
        id_coords.insert({id, std::make_pair(std::stod(values.at(3)), std::stod(values.at(4)))});
        id++;
        values.clear();
    }
}
