cmake_minimum_required(VERSION 3.15)
project(CFG)

set(CMAKE_CXX_STANDARD 17)

add_executable(CFG main.cpp src/CFG.cpp src/CFG.h src/PDA.cpp src/PDA.h src/StatePDA.cpp src/StatePDA.h)