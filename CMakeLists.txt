cmake_minimum_required(VERSION 3.16)
project(os-labs)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if (UNIX AND NOT APPLE)
        add_compile_options(
                -fdiagnostics-color=always
                -Wall
                -Werror
                -Wextra
                -Wpedantic
                -pedantic-errors
                -Wcast-align
                -Wcast-qual
                -Wconversion
                -Wctor-dtor-privacy
                -Wduplicated-branches
                -Wextra-semi
                -Wenum-compare
                -Wfloat-equal
                -Wnon-virtual-dtor
                -Woverloaded-virtual
                -Wredundant-decls
                -Wsign-conversion
                -Wsign-promo
                -Wpadded
        )
    endif()
endif()

set(CMAKE_CXX_CPPCHECK "cppcheck")
if (CMAKE_CXX_CPPCHECK)
    list(
            APPEND CMAKE_CXX_CPPCHECK
            "-v"
            "--template=gcc"
            "--addon=cert.py"
            "--addon=y2038.py"
            "--addon=threadsafety.py"
            "--enable=all"
            "--inconclusive"
            "--force"
            "--std=c++${CMAKE_CXX_STANDARD}"
    )
endif()

add_subdirectory(src)
