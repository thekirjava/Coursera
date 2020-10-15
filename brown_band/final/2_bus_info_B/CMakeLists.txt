cmake_minimum_required(VERSION 3.17)
project(2_bus_info_B)

set(CMAKE_CXX_STANDARD 20)

add_executable(2_bus_info_B main.cpp coordinates.cpp coordinates.h database.cpp database.h manager.cpp manager.h request.cpp request.h)