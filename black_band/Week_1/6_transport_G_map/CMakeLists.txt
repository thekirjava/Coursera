cmake_minimum_required(VERSION 3.17)
project(6_transport_G_map)

set(CMAKE_CXX_STANDARD 17)

add_executable(6_transport_G_map main.cpp coordinates.h coordinates.cpp database.h database.cpp graph.h json.h json.cpp manager.h manager.cpp request.h request.cpp router.h svg.h svg.cpp linker.h map.cpp map.h route.cpp route.h)