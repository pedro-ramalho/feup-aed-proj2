#pragma once

#include <string>
#include <vector>
#include <iostream>

class Menu {
private:
    std::vector<std::string> main_menu_prompts;
    std::vector<std::string> bus_ride_prompts;
public:
    Menu();
    
    void print_prompts(std::vector<std::string> prompts);
};