cmake_minimum_required (VERSION 2.6)
project (Algorithms)

# The version number.
set (Algorithms_VERSION_MAJOR 1)
set (Algorithms_VERSION_MINOR 0)

# Flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++17 -Wextra -pthread -isystem")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")

add_subdirectory(test test)
