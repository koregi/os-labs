set(CXX_STANDARD 17)
set(GNU_CXX_WARNINGS "-Werror -pedantic-errors -Wall -Wextra -Wpedantic\
    -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wduplicated-branches -Wduplicated-cond\
    -Wextra-semi -Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Woverloaded-virtual\
    -Wredundant-decls -Wsign-conversion -Wsign-promo -Wpadded")
set(GNU_CXX_COLORS "-fdiagnostics-color=always")
set(GNU_CXX_SANITIZERS "-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all\
    -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment\
    -fsanitize=leak -fsanitize-address-use-after-scope -g")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${GNU_CXX_WARNINGS} ${GNU_CXX_COLORS}")
endif()

set(CMAKE_CXX_CPPCHECK "cppcheck")
if(CMAKE_CXX_CPPCHECK)
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
            "--std=c++${CXX_STANDARD}"
    )
endif()
