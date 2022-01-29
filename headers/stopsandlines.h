#pragma once

#include <map>
#include <fstream>
#include <algorithm>
#include "../headers/lines.h"

class StopsAndLines {
private:
    /**
     * @brief Maps a pair containing the code of a Stop and it's name to an ID
     */
    std::map<std::pair<std::string, std::string>, int> stopscode_line_to_id;

    /**
     * @brief Maps an ID to a line
     */
    std::map<int, std::string> id_to_line;

    /**
     * @brief Maps an ID of a Stop to a pair containing the latitude and longitude
     */
    std::map<int, std::pair<double, double>> id_to_coords;

    /**
     * @brief Maps an ID to a pair containing the code of a Stop and it's Line
     */
    std::map<int, std::pair<std::string, std::string>> id_to_code_line;

    /**
     * @brief Maps an ID of a Stop to it's zone
     */
    std::map<int, std::string> id_to_zone;

    /**
     * @brief Stores the paths to every Line file inside the dataset directory
     * 
     */
    std::vector<std::string> line_paths;

    /**
     * @brief Data class storing all lines
     */
    Lines lines;

    /**
     * @brief Data class storing all stops
     */
    Stops stops;

    /**
     * @brief Constructs the maps above by using the Stops and Lines objects
     */
    void read_stops_and_lines();

public:
    /**
     * @brief Construct a new Stops And Lines object
     */
    StopsAndLines();

    /**
     * @brief Get the line paths
     * @return std::vector<std::string> 
     */
    std::vector<std::string> get_line_paths() const;

    /**
     * @brief Get the coordinates of a Stop given it's ID
     * @param id ID of a Stop
     * @return std::pair<double, double> containing the latitude and longitude
     */
    std::pair<double, double> get_coords(int id) const;

    /**
     * @brief Get the line given it's ID
     * @param id ID of a Line
     * @return the line name
     */
    std::string get_line(int id) const;

    /**
     * @brief Get the zone given it's ID
     * @param id ID of a Stop
     * @return the zone name
     */
    std::string get_zone(int id) const;

    /**
     * @brief Get the code and the line of a Stop given it's ID
     * @param id ID of a Stop
     * @return std::pair<std::string, std::string> containing the code and the line of a Stop
     */
    std::pair<std::string, std::string> get_code_line(int id) const;

    /**
     * @brief Get the codes of the Stops inside the "path" file
     * @param path path to the line file
     * @return std::vector<std::string> containing the codes of the Stops of the given line
     */
    std::vector<std::string> get_codes(std::string path) const;

    /**
     * @brief Get the ID of the pair containing the code and line of a Stop
     * @param code of the Stop
     * @param line of the Stop
     * @return ID of the given the pair
     */
    int get_stop_line_id(std::string code, std::string line) const;

    /**
     * @brief Adds new elements to the maps above
     * @param code code of a Stop
     * @param id ID representing either a Stop ID, Line ID
     * @param name name of a Stop
     * @param zone zone of a Stop
     * @param coords latitude and longitude of a Stop
     * @param line name of a Line
     */
    void add_stop_and_line(std::string code, int id, std::string name, std::string zone, std::pair<double, double> coords, std::string line);
};