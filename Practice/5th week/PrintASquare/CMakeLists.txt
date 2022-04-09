cmake_minimum_required(VERSION 3.21)
project(PrintASquare)

set(CMAKE_CXX_STANDARD 20)

add_executable(PrintASquare main.cpp)
target_include_directories(PrintASquare PUBLIC ../../../Common/src)
