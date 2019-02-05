cmake_minimum_required(VERSION 3.13)
project(second_try)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable( goal
        main.cpp
        Matrix.h
        Row.cpp
        Matrix.cpp
        README.md)
