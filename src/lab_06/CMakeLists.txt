cmake_minimum_required(VERSION 3.16)
project(lab_06)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_06_1 lab_06_1.cpp)
target_link_libraries(lab_06_1 pthread rt)

add_executable(lab_06_2 lab_06_2.cpp)
target_link_libraries(lab_06_2 pthread rt)