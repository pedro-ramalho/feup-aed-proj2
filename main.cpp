#include <iostream>
#include <filesystem>
#include "headers/utils.h"
#include "headers/graphs/graph.h"
#include "headers/stops.h"
#include "headers/lines.h"
#include "headers/stopsandlines.h"
#include "headers/graphs/stopgraph.h"
#include "headers/graphs/distancegraph.h"

int main() {

    Stops stops;

    Lines lines;

    std::string src_stop, dest_stop;

    StopGraph graph(stops, lines, 2488, 0.25);


    DistanceGraph d_graph(stops, lines, 2487, 0.25);


    std::cout << "Insira o código da paragem de partida: "; std::cin >> src_stop;
    std::cout << "ID da paragem: " << stops.get_id(src_stop) << std::endl;
    std::cout << "Insira o código da paragem de destino: "; std::cin >> dest_stop;
    std::cout << "ID da paragem: " << stops.get_id(dest_stop) << std::endl;

    std::list<int> best_path = d_graph.dijkstra_path(stops.get_id(src_stop), stops.get_id(dest_stop));

    if (best_path.empty()) std::cout << "Empty list" << std::endl;
    
    std::cout << '\n';

    std::cout << "Melhor caminho: " << std::endl;

    std::cout << '\n';

    
    //linha usada (ou a pé), nome da paragem, código da paragem, zona da paragem 


    for (auto it = best_path.begin(); it != best_path.end(); it++) {
         std::cout << "-> linha usada: " << graph.get_nodes()[*it].line_used << " - " << stops.get_name_zone(*it).first << " (" << stops.get_code(*it) << ")" << " - " << stops.get_name_zone(*it).second << " - distância disponivel: " << graph.get_nodes()[*it].distance_available << std::endl;
    }
    return 0;
}