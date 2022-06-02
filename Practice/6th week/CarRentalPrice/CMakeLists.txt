cmake_minimum_required(VERSION 3.21)
project(CarRentalPrice)

set(CMAKE_CXX_STANDARD 20)

add_executable(CarRentalPrice main_selfContained.cpp)
add_library(Common "../../../Common/src/common.cpp")

target_link_libraries(CarRentalPrice PUBLIC Common)
target_include_directories(CarRentalPrice PUBLIC ../../../Common/src)
