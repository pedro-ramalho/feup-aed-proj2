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

const std::string STOPS_FILE = "dataset/stops.csv";

#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

void clear_screen();

void read_stops_file();

std::pair<std::string, std::string> get_code(int id);

std::string get_zone(int id);

std::pair<double, double> get_coords(int id);

double haversine(double lat1, double lon1, double lat2, double lon2);