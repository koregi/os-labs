cmake_minimum_required(VERSION 3.16)
project(lab_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} lab_01.cpp)
add_executable(extra_task extra_task_01.cpp)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(extra_task pthread)
