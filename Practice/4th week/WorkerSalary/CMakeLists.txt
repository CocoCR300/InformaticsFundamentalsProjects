cmake_minimum_required(VERSION 3.21)
project(WorkerSalary)

set(CMAKE_CXX_STANDARD 20)

add_executable(WorkerSalary main.cpp)
target_include_directories(WorkerSalary PUBLIC ../../../Common/src)
