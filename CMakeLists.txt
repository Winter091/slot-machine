cmake_minimum_required(VERSION 3.01)

project(slot-machine LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED YES)

add_executable(
    slot-machine 
    src/main.cpp
)

target_compile_options(slot-machine PRIVATE -Wall -Wextra)

