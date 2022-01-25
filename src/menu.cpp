#include "../headers/menu.h"

Menu::Menu() {
    this->main_menu_prompts = {"1) Menor número de paragens", "2) Menor distância", "3) Menor número de mudanças de linha", "4) Mais barato (passa por menos zonas)"};
}

void Menu::print_propmts(std::vector<std::string> prompts) {
    for (const std::string prompt : prompts)
        std::cout << prompt << std::endl;
}