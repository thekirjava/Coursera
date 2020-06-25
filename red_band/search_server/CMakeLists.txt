cmake_minimum_required(VERSION 3.16)
project(search_server)

set(CMAKE_CXX_STANDARD 17)

add_executable(search_server main.cpp iterator_range.h parse.cpp parse.h profile.h search_server.cpp search_server.h test_runner.h)