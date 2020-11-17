cmake_minimum_required(VERSION 3.17)
project(7_transport_M)

set(CMAKE_CXX_STANDARD 20)

add_executable(7_transport_M descriptions.h descriptions.cpp graph.h json.h json.cpp map_renderer.h map_renderer.cpp requests.h requests.cpp router.h sphere.h sphere.cpp sphere_projection.h sphere_projection.cpp svg.h svg.cpp transport_catalog.h transport_router.cpp transport_router.h transport_router.cpp utils.h utils.cpp main.cpp)