cmake_minimum_required(VERSION 3.21)
project(SquareAndRectangleAreaCalculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(SquareAndRectangleAreaCalculator src/main.cpp)
# add_library(Common "../../../Common/src/common.cpp")

# target_link_libraries(SquareAndRectangleAreaCalculator PUBLIC Common)

target_include_directories(SquareAndRectangleAreaCalculator PUBLIC "../../../Common/src")
