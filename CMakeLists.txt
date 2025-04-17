cmake_minimum_required(VERSION 3.26)
project(EmergencyResponseGraph)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Main
        src/EmergencyResponseGraph.cpp
        src/EmergencyResponseGraph.h
        src/main.cpp)
