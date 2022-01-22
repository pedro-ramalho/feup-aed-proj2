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

double haversine(std::pair<double, double> c1, std::pair<double, double> c2);

double haversine(double lat1, double lon1, double lat2, double lon2);