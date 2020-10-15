cmake_minimum_required(VERSION 3.17)
project(2_mython_lexer)

set(CMAKE_CXX_STANDARD 20)

add_executable(2_mython_lexer main.cpp test_runner.h lexer.cpp lexer.h)