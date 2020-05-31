cmake_minimum_required(VERSION 3.16)
project(server_stats)

set(CMAKE_CXX_STANDARD 17)

add_executable(server_stats main.cpp stats.h http_request.h stats.cpp)