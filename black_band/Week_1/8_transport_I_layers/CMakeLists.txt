cmake_minimum_required(VERSION 3.17)
project(8_transport_I_layers)

set(CMAKE_CXX_STANDARD 20)

add_executable(8_transport_I_layers main.cpp coordinates.h coordinates.cpp database.h database.cpp graph.h json.h json.cpp linker.h manager.h manager.cpp map.h map.cpp request.h request.cpp route.h route.cpp router.h svg.h svg.cpp)