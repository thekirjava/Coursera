cmake_minimum_required(VERSION 3.17)
project(7_transport_H_numbers)

set(CMAKE_CXX_STANDARD 20)

add_executable(7_transport_H_numbers main.cpp coordinates.h coordinates.cpp database.h database.cpp graph.h json.cpp json.h linker.h manager.cpp manager.h map.cpp map.h request.cpp request.h route.cpp route.h router.h svg.cpp svg.h)