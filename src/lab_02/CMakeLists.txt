cmake_minimum_required(VERSION 3.16)
project(lab_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_02_1 lab_02_1.cpp)
target_link_libraries(lab_02_1 pthread)

add_executable(lab_02_2 lab_02_2.cpp)
target_link_libraries(lab_02_2 pthread)

add_executable(lab_02_3 lab_02_3.cpp)
target_link_libraries(lab_02_3 pthread)
