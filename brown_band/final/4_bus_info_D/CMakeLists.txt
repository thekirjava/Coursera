cmake_minimum_required(VERSION 3.17)
project(4_bus_info_D)

set(CMAKE_CXX_STANDARD 20)

add_executable(4_bus_info_D main.cpp coordinates.cpp coordinates.h database.cpp database.h manager.cpp manager.h request.cpp request.h json.cpp json.h)