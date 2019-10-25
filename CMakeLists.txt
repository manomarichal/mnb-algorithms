cmake_minimum_required(VERSION 3.10.2)
project(indiv)

set(CMAKE_CXX_STANDARD 17)

add_executable(indiv main.cpp src/CFG.cpp src/CFG.h src/PDA.cpp src/PDA.h src/StatePDA.cpp src/StatePDA.h src/algorithms.cpp src/algorithms.h)

#set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wnon-virtual-dtor -Wold-style-cast -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2")

# -Wall
# -Werror # treat all warnings as errors
#- Wextra # reasonable and standard
# -Wshadow # warn the user if a variable declaration shadows one from a parent context
# -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor
# -Wold-style-cast # warn for c-style casts
# -Wcast-align # warn for potential performance problem casts
# -Wunused # warn on anything being unused
# -Woverloaded-virtual # warn if you overload (not override) a virtual function
# -Wpedantic # warn if non-standard C++ is used
# -Wconversion # warn on type conversions that may lose data
# -Wsign-conversion # warn on sign conversions
# -Wnull-dereference # warn if a null dereference is detected
# -Wdouble-promotion # warn if float is implicit promoted to double
# -Wformat=2 # warn on security issues around functions that format output (ie printf)