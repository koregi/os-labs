cmake_minimum_required(VERSION 3.16)
project(lab_03)

set(CMAKE_CXX_STANDARD 17 -Wconversion -Wsign-conversion)

add_executable(lab_03_1 lab_03_1.cpp)
target_link_libraries(lab_03_1 pthread)

add_executable(lab_03_2 lab_03_2.cpp)
target_link_libraries(lab_03_2 pthread)