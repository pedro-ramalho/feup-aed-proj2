#include <iostream>
#include <filesystem>
#include "headers/utils.h"
#include "headers/graphs/graph.h"
#include "headers/stops.h"
#include "headers/lines.h"
#include "headers/graphs/stopsandlines.h"
#include "headers/graphs/stopgraph.h"

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

    Stops stops;

    Lines lines;

    std::string src_stop, dest_stop;

    StopGraph graph(stops, lines, 2488, 0.25);


    std::cout << "Insira o código da paragem de partida: "; std::cin >> src_stop;
    std::cout << "ID da paragem: " << stops.get_id(src_stop) << std::endl;
    std::cout << "Insira o código da paragem de destino: "; std::cin >> dest_stop;
    std::cout << "ID da paragem: " << stops.get_id(dest_stop) << std::endl;

    std::list<int> best_path = graph.bfs_path(stops, stops.get_id(src_stop), stops.get_id(dest_stop));

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