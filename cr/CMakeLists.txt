cmake_minimum_required(VERSION 4.0)
project(crv2)

set(CMAKE_CXX_STANDARD 20)

add_executable(crv2 main.cpp
        Graph.h
        Graph.cpp
        application.cpp)
