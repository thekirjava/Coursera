cmake_minimum_required(VERSION 3.17)
project(4_booking)

set(CMAKE_CXX_STANDARD 17)

add_executable(4_booking main.cpp new_trip_manager.h new_booking_providers.h booking.h)