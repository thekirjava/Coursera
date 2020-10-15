cmake_minimum_required(VERSION 3.17)
project(3_transport_E_asan)

set(CMAKE_CXX_STANDARD 20)

add_executable(3_transport_E_asan main.cpp descriptions.cpp descriptions.h graph.h json.cpp json.h requests.cpp requests.h router.h sphere.cpp sphere.h transport_catalog.cpp transport_catalog.h transport_router.cpp transport_router.h utils.cpp utils.h)