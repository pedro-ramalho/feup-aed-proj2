#include "../headers/menu.h"

Menu::Menu() {
    this->main_menu_prompts = {"1) Paragem", "2) Local"};

    this->day_night_prompts = {"1) De dia", "2) De noite"};
    
    this->bus_ride_prompts = {"1) Menor número de paragens", "2) Menor distância", "3) Menor número de mudanças de linha", "4) Mais barato (passa por menos zonas)"};

    this->stop_place_prompts = {"1) Paragem", "2) Local"};
}

void Menu::print_prompts(std::vector<std::string> prompts) {
    for (const std::string prompt : prompts){
        std::cout << prompt << std::endl;
    }

    std::cout << "\n\nOption:";
}

void Menu::run() {

    int choice = 0;
    int criteria = 0;

    do {
        std::cout << "que tipo de caminho vai ser bossman?\n\n";
        print_prompts(bus_ride_prompts);

        std::cin >> criteria;
        clear_screen();
    } while (criteria < 1 || criteria > 4);

    do {
        std::cout << "e agora queres escolher uma paragem ou um local? (de partida)\n\n";
        print_prompts(stop_place_prompts);

        std::cin >> choice;
        clear_screen();
    } while (choice < 1 || choice > 2);


    int src_id = 0;
    std::pair<double, double> src_coords;

    switch (choice) {
        case 1: 
            src_id = stop_option(criteria);
            break;
        
        case 2: 
            src_coords = coords_option();
            break;
    }

    double walking_distance = 0;

    do {
        std::cout << "Quanto está disposto a andar? : ";
        std::cin >> walking_distance;
        clear_screen();
    } while (walking_distance < 0);

    choice = 0;

    do {
        std::cout << "e agora queres escolher uma paragem ou um local? (de chegada)\n\n";
        print_prompts(stop_place_prompts);

        std::cin >> choice;
        clear_screen();
    } while (choice < 1 || choice > 2);

    int dest_id = 0;
    std::pair<double, double> dest_coords;

    switch (choice) {
        case 1: 
            dest_id = stop_option(criteria);
            break;
        
        case 2: 
            dest_coords = coords_option();
            break;
    }

}


void Menu::best_path(int criteria, double walking_distance, int src_id, int dest_id, std::pair<double, double> src_coords, std::pair<double, double> dest_coords) {
    std::list<int> path = std::list<int>();
    
    if (src_id == 0 && dest_id == 0) { //both as positions
        switch (criteria) {
            case 1: // menor número de paragens
                {
                Stops stop;
                stop.add_stop("SRC", 2488, "Posição Inicial", "NATUR", src_coords);
                stop.add_stop("DEST", 2489, "Posição Final", "NATUR", dest_coords);
                StopGraph s_graph(stop, lines, 2480, walking_distance);
                
                for (int i = 1; i <= NUM_STOPS; i++) {
                    if (haversine(stop.get_coords(i), src_coords) <= walking_distance) {
                        s_graph.add_edge(i, 2488, 0, "A pé");
                    }
                }

                path = s_graph.bfs_path(stop, 2488, 2489);
                //this->print_best_path(path);
                }
                break;
            case 2: // menor distância
                {
                DistanceGraph d_graph();
                }
                break;
            case 3: //menor numero de mudanças de linhas
                {
                LineGraph l_graph();
                }
                break;
            case 4: //menor numero de zonas
                {
                ZoneGraph z_graph();
                }
                break;
        }
    }
    else if (src_id > 0 && dest_id > 0) { //both as ids
        switch (criteria) {
            case 1: // menor número de paragens
                StopGraph s_graph();
                break;
            case 2: // menor distância
                DistanceGraph d_graph();
                break;
            case 3: //menor numero de mudanças de linhas
                LineGraph l_graph();
                break;
            case 4: //menor numero de zonas
                ZoneGraph z_graph();
                break;
        }
    }
    else if (src_id > 0 && dest_id == 0) { //destination is a position, src is a stop
        switch (criteria) {
            case 1: // menor número de paragens
                StopGraph s_graph();
                break;
            case 2: // menor distância
                DistanceGraph d_graph();
                break;
            case 3: //menor numero de mudanças de linhas
                LineGraph l_graph();
                break;
            case 4: //menor numero de zonas
                ZoneGraph z_graph();
                break;
        }
    }
    else if (src_id == 0 && dest_id > 0) { //src is a position, destination is a stop
        switch (criteria) {
            case 1: // menor número de paragens
                StopGraph s_graph();
                break;
            case 2: // menor distância
                DistanceGraph d_graph();
                break;
            case 3: //menor numero de mudanças de linhas
                LineGraph l_graph();
                break;
            case 4: //menor numero de zonas
                ZoneGraph z_graph();
                break;
        } 
    } 
    else {
        std::cerr << "ERROR AT MEM.ADDR 0x00B00B1E5\n FLUSHING CORE AND DUMPING TO BIOS\n !!CAREFUL!! IP IS VULNERABLE\n" << std::endl;
    }

}


int Menu::stop_option(int criteria) {
    std::string stop_code;

    std::cout << "Insira o código da paragem: "; std::cin >> stop_code;

    if (criteria == 3) {
        int i = 1;
        while (i < MAX_NUM_PAIRS) {
            if (stops_and_lines.get_code_line(i).first == stop_code) 
                return i;
            i++;                

        }
        return -1;
    }

    return this->stops.get_id(stop_code);
}

std::pair<double, double> Menu::coords_option() {
    double latitude, longitude;

    std::cout << "Insira a latitude: "; std::cin >> latitude;
    std::cout << "Insira a longitude: "; std::cin >> longitude;

    return {std::make_pair(latitude, longitude)};
}