#include <iostream>
#include <filesystem>
#include "headers/utils.h"
#include "headers/graphs/graph.h"
#include "headers/stops.h"
#include "headers/lines.h"
#include "headers/stopsandlines.h"
#include "headers/graphs/stopgraph.h"
#include "headers/graphs/distancegraph.h"
#include "headers/graphs/zonegraph.h"
#include "headers/graphs/linegraph.h"
#include <chrono>

int main() {

    Stops stops;

    Lines lines;

    StopsAndLines stops_and_lines;

    std::string src_stop, dest_stop;

    StopGraph graph(stops, lines, 2488, 0.25);

    DistanceGraph d_graph(stops, lines, 2487, 0.28);

    ZoneGraph z_graph(stops, lines, 2487, 0.28);

    LineGraph l_graph(stops_and_lines, 5262, 0.0);


    std::vector<int> src_stops;
    std::vector<int> dest_stops;
    std::cout << "Insira o código da paragem de partida: "; std::cin >> src_stop;
    
    std::cout << "Insira o código da paragem de destino: "; std::cin >> dest_stop;
    int src_id, dest_id;

    // os meus olhos estão a sangrar de pensar neste código 💀
    // problem CPU? 😂
    
    bool c1 = false, c2 = false;
    int i = 1;
    while (true) {
        if (i > 5262) break;
        if (c1 && c2) break;

        std::cout << stops_and_lines.get_code_line(i).first << " i: " << i << std::endl;
        if (stops_and_lines.get_code_line(i).first == src_stop) {
            src_id = i;
            c1 = true;
        }
        
        if (stops_and_lines.get_code_line(i).first == dest_stop) {
            dest_id = i;
            c2 = true;
        }
        i++;
    }
    if (!c1 || !c2) {
        std::cout << "mete uma paragem valida" << std::endl;
        std::cin >> src_stop; // nonsense
    }


    std::list<int> best_path = l_graph.dijkstra_path(stops_and_lines, src_id, dest_id);

    if (best_path.empty()) std::cout << "Empty list" << std::endl;
    
    std::cout << '\n';

    std::cout << "Melhor caminho: " << std::endl;

    std::cout << '\n';

/*
    for (auto it = best_path.begin(); it != best_path.end(); it++) {
          std::cout << "-> linha usada: " << l_graph.get_nodes()[*it].line_used << " - " << stops.get_name_zone(*it).first << " (" << stops.get_code(*it) << ")" << " - " << stops.get_name_zone(*it).second << " - distância disponivel: " << l_graph.get_nodes()[*it].distance_available << std::endl;
     }
*/
    for (auto it = best_path.begin(); it != best_path.end(); it++) {
          std::cout << "-> linha usada: " << l_graph.get_nodes()[*it].line_used << " - " << stops.get_name(stops_and_lines.get_code_line(*it).first) << " (" << stops_and_lines.get_code_line(*it).first << ")" << " - " << stops.get_zone(stops_and_lines.get_code_line(*it).first) << " - distância disponivel: " << l_graph.get_nodes()[*it].distance_available << std::endl;
     }

    return 0;
}