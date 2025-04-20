cmake_minimum_required(VERSION 3.26)
project(EmergencyResponseGraph)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Main
        src/EmergencyResponseGraph.h
        src/main.cpp
        src/EmergencyResponseBellmanFord.h
        src/EmergencyResponseGraph.cpp
        src/Djikstras.cpp
        src/EmergencyResponseBellmanFord.cpp
)
