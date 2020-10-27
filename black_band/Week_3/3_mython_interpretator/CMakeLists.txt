cmake_minimum_required(VERSION 3.17)
project(3_mython_interpretator)

set(CMAKE_CXX_STANDARD 20)

add_executable(3_mython_interpretator comparators.h comparators.cpp main.cpp object.h object.cpp object_holder.h object_holder.cpp object_holder_test.cpp object_test.cpp parse.h parse.cpp parse_test.cpp statement.h statement.cpp statement_test.cpp lexer.cpp lexer.h)