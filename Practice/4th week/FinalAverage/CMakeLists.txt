cmake_minimum_required(VERSION 3.21)
project(FinalAverage)

set(CMAKE_CXX_STANDARD 20)

add_executable(FinalAverage main.cpp)
target_include_directories(FinalAverage PUBLIC ../../../Common/src)