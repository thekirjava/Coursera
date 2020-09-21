cmake_minimum_required(VERSION 3.17)
project(1_bus_info_A)

set(CMAKE_CXX_STANDARD 20)

add_executable(1_bus_info_A main.cpp coordinates.cpp coordinates.h database.cpp database.h manager.cpp manager.h)