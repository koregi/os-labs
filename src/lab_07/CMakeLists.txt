cmake_minimum_required(VERSION 3.16)
project(lab_07)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_07_1 lab_07_1.cpp)
target_link_libraries(lab_07_1 pthread rt)

add_executable(lab_07_2 lab_07_2.cpp)
target_link_libraries(lab_07_2 pthread rt)