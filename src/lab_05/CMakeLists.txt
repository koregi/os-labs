cmake_minimum_required(VERSION 3.16)
project(lab_05)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_05_1 lab_05_1.cpp)
target_link_libraries(lab_05_1 pthread)

add_executable(lab_05_2 lab_05_2.cpp)
target_link_libraries(lab_05_2 pthread)
