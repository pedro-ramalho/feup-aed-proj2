
#pragma once

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

class Stops {
private:
    /**
     * @brief Maps a Stop code to an ID
     */
    std::map<std::string, int> code_id;

    /**
     * @brief Maps an ID to a Stop code
     */
    std::map<int, std::string> id_to_code;

    /**
     * @brief Maps an ID to a pair of the name of a Stop and it's zone
     */
    std::map<int, std::pair<std::string, std::string>> id_name_zone;

    /**
     * @brief Maps an ID to a pair of the latitude and longitude of a Stop
     */
    std::map<int, std::pair<double, double>> id_coords;

    /**
     * @brief Maps a Stop code to it's zone
     */
    std::map<std::string, std::string> code_to_zone;

    /**
     * @brief Maps a Stop code to it's real name
     */
    std::map<std::string, std::string> code_to_name;

    const std::string STOPS_FILE = "dataset/stops.csv";

    /**
     * @brief Reads stops.csv and constructs the maps above
     */
    void read_stops_file();

public:
    /**
     * @brief Construct a new Stops object
     */
    Stops();

    /**
     * @brief Get the ID of a Stop given it's code
     * @param code code of the Stop
     * @return ID of the Stop
     */
    int get_id(std::string code) const;

    /**
     * @brief Get the code of the Stop given it's ID
     * @param id ID of the Stop
     * @return code of the Stop 
     */
    std::string get_code(int id) const;

    /**
     * @brief Get the zone of a Stop given it's code
     * @param code code of the Stop
     * @return zone of the Stop
     */
    std::string get_zone(std::string code) const;

    /**
     * @brief Get the real name of a Stop given it's name
     * @param code code of the Stop
     * @return real name of the Stop 
     */
    std::string get_name(std::string code) const;

    /**
     * @brief Get the real name and the zone of a Stop given it's ID
     * @param id ID of the Stop
     * @return pair of the real name and zone of the Stop
     */
    std::pair<std::string, std::string> get_name_zone(int id) const;

    /**
     * @brief Get the coordinates of a Stop given it's ID
     * @param id ID of the Stop
     * @return pair of the latitude and longitude of the Stop
     */
    std::pair<double, double> get_coords(int id) const;

    /**
     * @brief Adds new elements to every map above
     * @param code code of the Stop
     * @param id ID of the Stop
     * @param name real name of the Stop
     * @param zone zone of the Stop
     * @param coords pair containing the latitude and longitude of the Stop
     */
    void add_stop(std::string code, int id, std::string name, std::string zone, std::pair<double, double> coords);

};
