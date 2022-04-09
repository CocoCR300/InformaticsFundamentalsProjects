cmake_minimum_required(VERSION 3.21)
project(ShoppingCart)

set(CMAKE_CXX_STANDARD 20)

add_executable(ShoppingCart main.cpp)
target_include_directories(ShoppingCart PUBLIC ../../../Common/src)
