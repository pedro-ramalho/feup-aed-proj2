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

    /**
     * @brief All the existing lines
     * 
     */
    Lines lines;

    /**
     * @brief All the existing stops
     * 
     */
    Stops stops;

    /**
     * @brief Data class storing all existing pairs of a Stop and a Line
     * 
     */
    StopsAndLines stops_and_lines;

    /**
     * @brief The prompts asking what type of shortest path the user wants to know
     * 
     */
    std::vector<std::string> bus_ride_prompts;

    /**
     * @brief The prompts asking whether the user wants to choose a stop or a location
     * 
     */
    std::vector<std::string> stop_place_prompts;

    /**
     * @brief Asks the user for info about a stop
     * 
     * @param criteria - the type of shortest path the user chose 
     * @return int correspondent to the stop
     */
    int stop_option(int criteria);

    /**
     * @brief Asks the user for the coordinates of a location
     * 
     * @return a pair storing the latitude and longitude
     */
    std::pair<double, double> coords_option();

    /**
     * @brief Calculates the best path from a graph and calls the correspondent print_best_path() function
     * 
     * @param criteria the type of shortest path chosen by the user
     * @param distance the max distance the user chose to walk
     * @param src_id the ID of the starting node
     * @param dest_id the ID of the destination node
     * @param src_coords the coordinates of the starting point
     * @param dest_coords the coordinates of the destination
     */
    void best_path(int criteria, double distance, int src_id, int dest_id, std::pair<double, double> src_coords, std::pair<double, double> dest_coords);

public:

    /**
     * @brief Construct a new Menu object
     * 
     */
    Menu();
    
    /**
     * @brief Print given prompts to screen
     * 
     * @param prompts 
     */
    void print_prompts(std::vector<std::string> prompts);

    /**
     * @brief Main run function of the menu
     * 
     */
    void run();

    /**
     * @brief Add a stop to the graph
     * 
     * @param id ID of the stop added
     * @param coords coordinates of the stop
     */
    void add_stop(int id, std::pair<double, double> coords);

    /**
     * @brief Prints out the best path travelling the least amount of stops
     * 
     * @param path the path to be printed out
     * @param graph the graph in question
     * @param stops all the existing stops
     */
    void print_best_path(std::list<int> path, StopGraph graph, const Stops& stops);
    
    /**
     * @brief Prints out the best path travelling the least distance
     * 
     * @param path the path to be printed out 
     * @param graph the graph in question 
     * @param stops all the existing stops 
     */
    void print_best_path(std::list<int> path, DistanceGraph graph, const Stops& stops);

    /**
     * @brief Prints out the best path switching lines the least amount of times
     * 
     * @param path the path to be printed out
     * @param l_graph the graph in question
     * @param s all the existing stops
     * @param s_l all the existing pairs of a Stop and a Line
     */
    void print_best_path(std::list<int> path, LineGraph l_graph, const Stops& s, const StopsAndLines& s_l);

    /**
     * @brief Prints out the best path switching zones the least amount of times
     * 
     * @param path the path to be printed out
     * @param graph the graph in question
     * @param stops all the existing stops
     */
    void print_best_path(std::list<int> path, ZoneGraph graph, const Stops& stops);


};