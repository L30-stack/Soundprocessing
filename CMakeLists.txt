cmake_minimum_required(VERSION 3.21)
project(Soundprocessing)

set(CMAKE_CXX_STANDARD 14)

add_executable(Soundprocessing main.cpp src/Header/Wave.cpp src/Header/Wave.h src/Header/Plotter.cpp src/Header/Plotter.h)
