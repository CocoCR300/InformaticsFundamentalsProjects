cmake_minimum_required(VERSION 3.21)
project(BMICalculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(BMICalculator main.cpp)
target_include_directories(BMICalculator PUBLIC ../../../Common/src)
