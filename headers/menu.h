#pragma once

#include <string>
#include <vector>
#include <iostream>

class Menu {
private:
    std::vector<std::string> main_menu_prompts;
public:
    Menu();
    
    void print_propmts(std::vector<std::string> prompts);
};