cmake_minimum_required(VERSION 3.16.3)

project(AED2122PROJ2)

add_executable(${PROJECT_NAME} main.cpp headers/utils.h src/utils.cpp headers/graphs/graph.h src/graphs/graph.cpp headers/stops.h src/stops.cpp headers/lines.h src/lines.cpp headers/menu.h src/menu.cpp headers/graphs/linegraph.h src/graphs/linegraph.cpp headers/stopsandlines.h src/stopsandlines.cpp headers/minheap.h headers/graphs/stopgraph.h src/graphs/stopgraph.cpp headers/graphs/zonegraph.h src/graphs/zonegraph.cpp headers/graphs/distancegraph.h src/graphs/distancegraph.cpp)
