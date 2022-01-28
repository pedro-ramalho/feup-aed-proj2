#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "stops.h"
#include "lines.h"
#include "stopsandlines.h"
#include "graphs/stopgraph.h"
#include "graphs/distancegraph.h"
#include "graphs/linegraph.h"
#include "graphs/zonegraph.h"

#define MAX_NUM_PAIRS 5264
#define NUM_STOPS 2487


class Menu {
private:
    Lines lines;
    Stops stops;
    StopsAndLines stops_and_lines;

    std::vector<std::string> main_menu_prompts;
    std::vector<std::string> day_night_prompts;
    std::vector<std::string> bus_ride_prompts;
    std::vector<std::string> stop_place_prompts;

    int stop_option(int criteria);

    std::pair<double, double> coords_option();

    void best_path(int criteria, double distance, int src_id, int dest_id, std::pair<double, double> src_coords, std::pair<double, double> dest_coords);

public:
    Menu();
    
    void print_prompts(std::vector<std::string> prompts);

    void run();

    void add_stop(int id, std::pair<double, double> coords);
};