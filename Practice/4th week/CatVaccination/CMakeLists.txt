cmake_minimum_required(VERSION 3.21)
project(CatVaccination)

set(CMAKE_CXX_STANDARD 20)

add_executable(CatVaccination main.cpp)
target_include_directories(CatVaccination PUBLIC ../../../Common/src)
