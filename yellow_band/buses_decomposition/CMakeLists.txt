cmake_minimum_required(VERSION 3.15)
project(buses_decomposition)

set(CMAKE_CXX_STANDARD 17)

add_executable(buses_decomposition main.cpp query.cpp query.h responses.cpp responses.h bus_manager.cpp bus_manager.h)