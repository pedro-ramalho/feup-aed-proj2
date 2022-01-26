cmake_minimum_required(VERSION 3.16.3)

project(AED2122PROJ2)

add_executable(${PROJECT_NAME} main.cpp headers/utils.h src/utils.cpp headers/graph.h src/graph.cpp headers/stops.h src/stops.cpp headers/lines.h src/lines.cpp headers/menu.h src/menu.cpp headers/linegraph.h src/linegraph.cpp headers/stopsandlines.h src/stopsandlines.cpp headers/minheap.h headers/stopgraph.h src/stopgraph.cpp)
