cmake_minimum_required(VERSION 3.21)
project(AnnualBudgetDistribution)

set(CMAKE_CXX_STANDARD 20)

add_executable(AnnualBudgetDistribution main.cpp)
target_include_directories(AnnualBudgetDistribution PUBLIC ../../../Common/src)