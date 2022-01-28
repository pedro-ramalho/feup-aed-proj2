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

    std::cout << "\n\n>> ";
}

void Menu::run() {

    int choice = 0;
    int criteria = 0;

    do {
        std::cout << "Indique o tipo de percurso que deseja: \n\n";
        print_prompts(bus_ride_prompts);

        std::cin >> criteria;
        clear_screen();
    } while (criteria < 1 || criteria > 4);

    double walking_distance = 0;

    do {
        std::cout << "Quanto está disposto a andar?\n";
        std::cout << ">> "; std::cin >> walking_distance;
        clear_screen();
    } while (walking_distance < 0);

    do {
        std::cout << "Quer começar numa paragem ou numa posição (coordenadas GPS)?\n\n";
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

    choice = 0;

    do {
        std::cout << "Quer terminar numa paragem ou numa posição (coordenadas GPS)?\n\n";
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

    this->best_path(criteria, walking_distance, src_id, dest_id, src_coords, dest_coords);

}


void Menu::best_path(int criteria, double walking_distance, int src_id, int dest_id, std::pair<double, double> src_coords, std::pair<double, double> dest_coords) {
    
    std::list<int> path = std::list<int>();
    
    if (src_id == 0 && dest_id == 0) { //both as positions
        switch (criteria) {
            case 1: // menor número de paragens
                {   
                    Stops stop;
                    stop.add_stop("SOURCE", 2488, "Posição Inicial", "NATUR", src_coords);
                    stop.add_stop("DEST", 2489, "Posição Final", "NATUR", dest_coords);
                    StopGraph s_graph(stop, lines, 2489, walking_distance);
                    
                
                    for (int i = 1; i <= NUM_STOPS; i++) {
                        if (haversine(stop.get_coords(i), src_coords) <= walking_distance) {
                            s_graph.add_edge(2488, i, 0, "A pé");
                        }
                    }

                    path = s_graph.bfs_path(stop, 2488, 2489);
                    this->print_best_path(path, s_graph, stop);
                }
                break;
            case 2: // menor distância
                {
                    Stops stop;
                    stop.add_stop("SOURCE", 2488, "Posição Inicial", "NATUR", src_coords);
                    stop.add_stop("DEST", 2489, "Posição Final", "NATUR", dest_coords);
                    DistanceGraph d_graph(stop, lines, 2489, walking_distance);
                
                    for (int i = 1; i <= NUM_STOPS; i++) {
                        if (haversine(stop.get_coords(i), src_coords) <= walking_distance) {
                            d_graph.add_edge(i, 2488, haversine(stop.get_coords(i), src_coords), "A pé");
                        }
                    }

                    path = d_graph.dijkstra_distance_path(stop, 2488, 2489).second;
                    this->print_best_path(path, d_graph, stop);
                }
                break;
            case 3: //menor numero de mudanças de linhas
                {
                    StopsAndLines s_l;
                    Stops stop;
                    stop.add_stop("SOURCE", 2488, "Posição Inicial", "NATUR", src_coords);
                    stop.add_stop("DEST", 2489, "Posição Final", "NATUR", dest_coords);
                    s_l.add_stop_and_line("SOURCE", 5263, "Posição Inicial", "NATUR", src_coords, "Caminho do 42");
                    s_l.add_stop_and_line("DEST", 5264, "Posição Final", "NATUR", dest_coords, "Caminho do 42");
                    LineGraph l_graph(s_l, 5264, walking_distance);

                    list<int> path = l_graph.dijkstra_distance_path(s_l, 5263, 5264).second;
                    this->print_best_path(path, l_graph, stop, s_l);
                }
                break;
            case 4: //menor numero de zonas
                {
                    Stops stop;
                    stop.add_stop("SOURCE", 2488, "Posição Inicial", "NATUR", src_coords);
                    stop.add_stop("DEST", 2489, "Posição Final", "NATUR", dest_coords);
                    ZoneGraph z_graph(stop, lines, 2489, walking_distance);
                
                    for (int i = 1; i <= NUM_STOPS; i++) {
                        if (haversine(stop.get_coords(i), src_coords) <= walking_distance) {
                            z_graph.add_edge(i, 2488, 0, "A pé");
                        }
                    }
                    
                    path = z_graph.dijkstra_distance_path(stop, 2488, 2489).second;
                    this->print_best_path(path, z_graph, stop);
                }
                break;
        }
    }
    else if (src_id > 0 && dest_id > 0) { //both as ids
        switch (criteria) {
            case 1: 
                {// menor número de paragens
                    StopGraph s_graph(stops, lines, NUM_STOPS, walking_distance);
                    path = s_graph.bfs_path(stops, src_id, dest_id);

                    this->print_best_path(path, s_graph, this->stops);
                }
                break;
            case 2: // menor distância
                {
                    DistanceGraph d_graph(stops, lines, NUM_STOPS, walking_distance);
                    std::list<int> path = d_graph.dijkstra_distance_path(stops, src_id, dest_id).second;

                    this->print_best_path(path, d_graph, this->stops);
                }
                break;
            case 3: //menor numero de mudanças de linhas
                {
                    StopsAndLines s_l;
                    LineGraph l_graph(s_l, 5262, walking_distance);

                    list<int> path = l_graph.dijkstra_distance_path(s_l, src_id, dest_id).second;
                    this->print_best_path(path, l_graph, this->stops, s_l);
                }
                break;
            case 4:
                { //menor numero de zonas
                    ZoneGraph z_graph(stops, lines, NUM_STOPS, walking_distance);
                    path = z_graph.dijkstra_distance_path(stops, src_id, dest_id).second;

                    this->print_best_path(path, z_graph, this->stops);
                }
                break;
        }
    }
    else if (src_id > 0 && dest_id == 0) { //destination is a position, src is a stop
        switch (criteria) {
            case 1:
                { // menor número de paragens
                    Stops stop;
                    stop.add_stop("DEST", 2488, "Posição Final", "NATUR", dest_coords);
                    StopGraph s_graph(stop, lines, 2488, walking_distance);

                    path = s_graph.bfs_path(stop, src_id, 2488);
                    this->print_best_path(path, s_graph, stop);
                }
                break;
            case 2: // menor distância
                {
                    Stops stop;
                    stop.add_stop("DEST", 2488, "Posição Final", "NATUR", dest_coords);
                    DistanceGraph d_graph(stop, lines, 2488, walking_distance);

                    path = d_graph.dijkstra_distance_path(stop, src_id, 2488).second;
                    this->print_best_path(path, d_graph, stop);
                }
                break;
            case 3: 
                {//menor numero de mudanças de linhas
                    StopsAndLines s_l;
                    Stops stop;
                    stop.add_stop("DEST", 2488, "Posição Final", "NATUR", dest_coords);
                    s_l.add_stop_and_line("DEST", 5263, "Posição Final", "NATUR", dest_coords, "Caminho do 42");
                    LineGraph l_graph(s_l, 5263, walking_distance);

                    list<int> path = l_graph.dijkstra_distance_path(s_l, src_id, 5263).second;
                    this->print_best_path(path, l_graph, stop, s_l);                    
                }
                break;
            case 4: 
                {//menor numero de zonas
                    Stops stop;
                    stop.add_stop("DEST", 2488, "Posição Final", "NATUR", dest_coords);
                    ZoneGraph z_graph(stop, lines, 2488, walking_distance);

                    path = z_graph.dijkstra_distance_path(stop, src_id, 2488).second;
                    this->print_best_path(path, z_graph, stop);
                }
                break;
        }
    }
    else if (src_id == 0 && dest_id > 0) { //src is a position, destination is a stop
        switch (criteria) {
            case 1: // menor número de paragens
                {
                    Stops stop;
                    stop.add_stop("SOURCE", 2488, "Posição Inicial", "NATUR", src_coords);
                    StopGraph s_graph(stop, lines, 2488, walking_distance);

                    for (int i = 1; i <= NUM_STOPS; i++) {
                        if (haversine(stop.get_coords(i), src_coords) <= walking_distance) {
                            s_graph.add_edge(2488, i, 0, "A pé");
                        }
                    }
                    
                    path = s_graph.bfs_path(stop, 2488, dest_id);
                    this->print_best_path(path, s_graph, stops);
                }
                break;
            case 2:
                { // menor distância
                    Stops stop;
                    stop.add_stop("SOURCE", 2488, "Posição Inicial", "NATUR", src_coords);
                    DistanceGraph d_graph(stop, lines, 2488, walking_distance);

                    for (int i = 1; i <= NUM_STOPS; i++) {
                        if (haversine(stop.get_coords(i), src_coords) <= walking_distance) {
                            d_graph.add_edge(2488, i, 0, "A pé");
                        }
                    }
                    
                    path = d_graph.dijkstra_distance_path(stop, 2488, dest_id).second;
                    this->print_best_path(path, d_graph, stops);
                }
                break;
            case 3: 
                {//menor numero de mudanças de linhas
                    StopsAndLines s_l;
                    Stops stop;
                    stop.add_stop("SOURCE", 2488, "Posição Inicial", "NATUR", src_coords);
                    s_l.add_stop_and_line("SOURCE", 5263, "Posição Inicial", "NATUR", src_coords, "Caminho do 42");
                    LineGraph l_graph(s_l, 5264, walking_distance);

                    list<int> path = l_graph.dijkstra_distance_path(s_l, 5263, dest_id).second;
                    this->print_best_path(path, l_graph, stop, s_l);
                }
                break;
            case 4: //menor numero de zonas
                { 
                    Stops stop;
                    stop.add_stop("SOURCE", 2488, "Posição Inicial", "NATUR", src_coords);
                    ZoneGraph z_graph(stop, lines, 2488, walking_distance);

                    for (int i = 1; i <= NUM_STOPS; i++) {
                        if (haversine(stop.get_coords(i), src_coords) <= walking_distance) {
                            z_graph.add_edge(2488, i, 0, "A pé");
                        }
                    }
                    
                    path = z_graph.dijkstra_distance_path(stop, 2488, dest_id).second;
                    this->print_best_path(path, z_graph, stops);
                }
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

void Menu::print_best_path(std::list<int> path, StopGraph graph, const Stops& s) {
    for (auto it = path.begin(); it != path.end(); it++) {
        std::cout << "-> Linha usada: " << graph.get_nodes()[*it].line_used << " - " << s.get_name_zone(*it).first << " (" << s.get_code(*it) << ")" << " - " << s.get_name_zone(*it).second << std::endl;
     }
}

void Menu::print_best_path(std::list<int> path, DistanceGraph graph, const Stops& s) {
    for (auto it = path.begin(); it != path.end(); it++) {
        std::cout << "-> linha usada: " << graph.get_nodes()[*it].line_used << " - " << s.get_name_zone(*it).first << " (" << s.get_code(*it) << ")" << " - " << s.get_name_zone(*it).second << " - distância disponivel: " << graph.get_nodes()[*it].distance_available << std::endl;
     }
}

void Menu::print_best_path(std::list<int> path, LineGraph l_graph, const Stops& s, const StopsAndLines& s_l) {
    for (auto it = path.begin(); it != path.end(); it++) {
        std::cout << "-> linha usada: " << l_graph.get_nodes()[*it].line_used << " - " << s.get_name(s_l.get_code_line(*it).first) << " (" << s_l.get_code_line(*it).first << ")" << " - " << s.get_zone(s_l.get_code_line(*it).first) << " - distância disponivel: " << l_graph.get_nodes()[*it].distance_available << std::endl;
    }
}

void Menu::print_best_path(std::list<int> path, ZoneGraph graph, const Stops& s) {
    std::cout << "Melhor percurso\n";

    for (auto it = path.begin(); it != path.end(); it++) {
        std::cout << "-> Linha usada: " << graph.get_nodes()[*it].line_used << " - " << s.get_name_zone(*it).first << " (" << s.get_code(*it) << ")" << " - " << s.get_name_zone(*it).second << " - distância disponivel: " << graph.get_nodes()[*it].distance_available << std::endl;
     }
}
