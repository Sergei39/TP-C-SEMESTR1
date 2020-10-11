cmake_minimum_required(VERSION 3.16)
project(iz-1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(iz_1 src/main.c src/logic.c src/my_math.c src/cl_console.c)

set(HEADER_FILES
        include/logic.h
        include/my_math.h
        )

set(SOURCE_FILES
        src/logic.c
        src/my_math.c
        )

add_library(iz-1 STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(Google_tests)
