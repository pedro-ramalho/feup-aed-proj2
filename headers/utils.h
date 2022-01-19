#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>
#include <cmath>

#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

void clear_screen();

double haversine(double lat1, double lon1, double lat2, double lon2);

std::vector<std::string> read_file(std::string filename);
