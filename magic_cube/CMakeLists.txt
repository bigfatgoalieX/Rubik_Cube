cmake_minimum_required(VERSION 3.10)
project(RubiksCubeSimulator)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(RubiksCubeSimulator main.cpp)

target_link_libraries(RubiksCubeSimulator sfml-graphics sfml-window sfml-system)
