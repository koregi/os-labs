cmake_minimum_required(VERSION 3.16)
project(lab_02)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} lab_02_1.cpp)
add_executable(lab_02_2 lab_02_2.cpp)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(lab_02_2 pthread)
