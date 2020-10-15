cmake_minimum_required(VERSION 3.17)
project(5_bus_info_E)

set(CMAKE_CXX_STANDARD 20)

add_executable(5_bus_info_E main.cpp coordinates.cpp coordinates.h database.cpp database.h json.cpp json.h manager.cpp manager.h request.cpp request.h graph.h router.h)