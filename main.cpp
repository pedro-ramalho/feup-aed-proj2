#include <iostream>
#include "headers/utils.h"

int main() {
    double lat1 = 51.5007;
    double lon1 = 0.1246;
    double lat2 = 40.6892;
    double lon2 = 74.0445;

    //should print 5574.84 km
    std::cout << haversine(lat1, lon1, lat2, lon2) << " km" << std::endl;
    return 0;
}