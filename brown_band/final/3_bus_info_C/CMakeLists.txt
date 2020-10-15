cmake_minimum_required(VERSION 3.17)
project(3_bus_info_C)

set(CMAKE_CXX_STANDARD 20)

add_executable(3_bus_info_C main.cpp coordinates.cpp coordinates.h database.cpp database.h manager.cpp manager.h request.cpp request.h)