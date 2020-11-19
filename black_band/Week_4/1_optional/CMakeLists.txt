cmake_minimum_required(VERSION 3.17)
project(1_optional)

set(CMAKE_CXX_STANDARD 20)

add_executable(1_optional test_runner.h main.cpp optional.h)