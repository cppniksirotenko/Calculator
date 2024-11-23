cmake_minimum_required(VERSION 3.14)

project(Calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Calculator main.cpp calculator.hpp calculator.cpp)
