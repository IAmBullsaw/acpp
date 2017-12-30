cmake_minimum_required(VERSION 3.9.6)
project(acpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++-4.0)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(20170112.assignment5.out exams/code20170112/assignment5.cpp)
add_executable(20170112.assignment6.out exams/code20170112/assignment6.cpp)
add_executable(20170112.assignment7.out exams/code20170112/assignment7.cpp)
add_executable(20170112.assignment8.out exams/code20170112/assignment8.cpp)

add_executable(20170420.assignment6.out exams/code20170420/assignment6.cpp)
