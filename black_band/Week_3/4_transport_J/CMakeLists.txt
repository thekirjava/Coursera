cmake_minimum_required(VERSION 3.17)
project(4_transport_J)

set(CMAKE_CXX_STANDARD 20)
add_executable(4_transport_J main.cpp coordinates.h coordinates.cpp database.h database.cpp graph.h json.h json.cpp linker.h manager.h manager.cpp map.h map.cpp request.h request.cpp router.h route.cpp svg.cpp svg.h)