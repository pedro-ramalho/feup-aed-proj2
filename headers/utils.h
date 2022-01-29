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


#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

/**
 * @brief Useful function to clear the terminal screen
 * 
 */
void clear_screen();

/**
 * @brief Haversine function to calculate distance from two sets of coordinates
 * 
 * @param c1 - first pair containing the latitude and longitude
 * @param c2 - second pair containing the latitude and longitude
 * @return the distance between the two locations
 */
double haversine(std::pair<double, double> c1, std::pair<double, double> c2);

/**
 * @brief Haversine function to calculate distance from two sets of coordinates
 * 
 * @param lat1 - the latitude of the first location
 * @param lon1 - the longitude of the first location
 * @param lat2 - the latitude of the second location
 * @param lon2 - the longitude of the second location
 * @return the distance between the two locations
 */
double haversine(double lat1, double lon1, double lat2, double lon2);