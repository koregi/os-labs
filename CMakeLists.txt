cmake_minimum_required(VERSION 3.16)
project(os-labs)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("debug mode")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/flags.cmake)
endif()

add_subdirectory(src)
