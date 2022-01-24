#include <iostream>
#include <filesystem>
#include "headers/utils.h"
#include "headers/graph.h"
#include "headers/stops.h"
#include "headers/lines.h"
#include "headers/stopsandlines.h"

//-----------------------------------------------------------------------------------------//
// *TAREFA FUNDAMENTAL*                                                                    //
// - dados dois locais, indicar o "melhor" percurso para ir de um local                    //
// para outro, usando para isso a rede dos STCP.                                           //
//                                                                                         //
// Para obter pontuação máxima devemos implementar diferentes versões                      //
// do que significa um "Local", do que significa "melhor percurso" e de                    //
// como pode uma pessoa mudar de linha.                                                    //
//                                                                                         //
// Local - tanto pode ser indicada diretamente uma paragem, como uma                       //
// localização (dada através das coordenadas, latitude e longitude)                        //
//                                                                                         //
// Melhor percurso - um utilizador pode querer o percurso que passa por                    //
// menos paragens, percorre menor distância, implica menos mudanças de                     //
// linha, fica mais barato (passa por menos zonas), etc.                                   //
//                                                                                         //           
// Mudar de autocarro - para além de mudar de autocarro numa paragem,                      //
// deve também ser possível caminhar um pouco para uma outra paragem                       //
// "vizinha" (que esteja a menos do que uma certa distância)                               //
//                                                                                         //
// O projeto deverá usar pelo menos uma vez o algoritmo de Dijkstra e                      //
// pesquisa em largura (BFS).                                                              //
//                                                                                         //
// Para cada método de carácter mais algorítmico deve ser indicada a                       //
// complexidade temporal associada.                                                        //
//                                                                                         //
// Temos ainda as seguintes tarefas de valorização extra:                                  //
//     1. permitir selecionar viagens diurnas ou noturnas (linhas com sufixo M)            //
//     2. ilustrar o uso de algoritmos para cálculo de MST's (podemos                      //
//     calcular a MST da rede global ou a MST de uma dada zona)                            //
//     3. possibilitar o fecho de paragens ou linhas selecionadas (ex: uma zona            //
//     estar com obras ou o utilizador fazer questão de não usar uma certa linha)          //
//     4. adicionar paragens e linhas de outros modos de transporte (ai)                   //
//                                                                                         //
//                                                                                         //
// Os dados estão disponíveis dentro do dir /dataset.                                      //
//                                                                                         //
// stops.csv                                                                               //
// Code,Name,Zone,Latitude,Longitude                                                       //
// - código da paragem, nome, latitude e longitude                                         //
//                                                                                         //
// lines.csv                                                                               //
// Code,Name                                                                               //
// - código da linha, nome da linha (as linhas terminadas em M são linhas que              //
// funcionam apenas de madrugada)                                                          //
//                                                                                         //
// lines_[LINECODE]_[DIR].csv                                                              //
// - a primeira linha contém um inteiro n que é o número de paragens. As n linhas          //
// seguintes indicam a sequência de paragens da linha, por ordem, indicando o percurso     //
// do autocarro. DIR indica a direção da linha, sendo que pode ser 0 (direção original)    //
// ou 1 (direção inversa)                                                                  //
//                                                                                         //
//-----------------------------------------------------------------------------------------//

int main() {
    // //creates an undirected graph with 9 nodes
    // Graph g(9, false);
    // g.add_edge(1,2);
    // g.add_edge(1,3);
    // g.add_edge(2,4);
    // g.add_edge(3,4);
    // g.add_edge(4,5);
    // g.add_edge(5,6);
    // g.add_edge(5,7);
    // g.add_edge(6,9);
    // g.add_edge(7,8);

    // Stops stops;

    // std::string stop_name;
    // std::cout << "Stop's code: "; std::cin >> stop_name;
    // std::cout << '\n';
    // int stop_id = stops.get_id(stop_name);
    // std::cout << "Stop ID = "  << stop_id << std::endl;
    // std::cout << '\n';
    // std::cout << "Stop's name: " << stops.get_name_zone(stop_id).first << std::endl;
    // std::cout << "Stop's zone: " << stops.get_name_zone(stop_id).second << std::endl;
    // std::cout << '\n';
    // std::cout << "Stop's latitude: " << stops.get_coords(stop_id).first << std::endl;
    // std::cout << "Stop's longitude: " << stops.get_coords(stop_id).second << std::endl;  

    Stops stops;

    Lines lines;

    std::string src_stop, dest_stop;

    Graph g = lines.get_stops_graph(0.0);


    std::cout << "Insira o código da paragem de partida: "; std::cin >> src_stop;
    std::cout << "ID da paragem: " << stops.get_id(src_stop) << std::endl;
    std::cout << "Insira o código da paragem de destino: "; std::cin >> dest_stop;
    std::cout << "ID da paragem: " << stops.get_id(dest_stop) << std::endl;

    std::list<int> best_path = g.dijkstra_path(stops.get_id(src_stop), stops.get_id(dest_stop));

    if (best_path.empty()) std::cout << "Empty list" << std::endl;
    
    std::cout << '\n';

    for (auto it = best_path.begin(); it != best_path.end(); it++)
        std::cout << "-> " << stops.get_name_zone(*it).first << " - " << stops.get_name_zone(*it).second << std::endl;

    std::cout << '\n';
    return 0;
}