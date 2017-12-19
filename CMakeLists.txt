cmake_minimum_required(VERSION 3.9.6)
project(acpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++-4.0)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(assignment5.out exams/code20170112/assignment5.cpp)
