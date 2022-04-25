cmake_minimum_required(VERSION 3.13)

project(slot-machine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(slot-machine)
add_subdirectory(src)

target_compile_options(slot-machine PRIVATE -Wall -Wextra)

target_link_libraries(
    slot-machine 
    sfml-graphics 
    sfml-window 
    sfml-system
)

target_include_directories(slot-machine PRIVATE ${CMAKE_SOURCE_DIR})
