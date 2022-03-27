cmake_minimum_required(VERSION 3.21)
project(TotalSalaryCalculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(TotalSalaryCalculator main.cpp)

target_include_directories(TotalSalaryCalculator PUBLIC "../../../Common")
