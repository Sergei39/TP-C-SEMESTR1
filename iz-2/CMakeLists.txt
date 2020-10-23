cmake_minimum_required(VERSION 3.6)
project(iz_2)

set(CMAKE_CXX_STANDARD 14)

set(ALL_SOURCE_FILES
        main.c
        )

#-------------------------static-lib-----------------------

set(SOURCE_FILES_STATIC_LIB
        src/naive_matrix.c
        src/matrix_member.c
        )
set(HEADER_FILES_STATIC_LIB
        include/naive_matrix.h
        include/matrix_member.h
        )
add_library(iz_2_static_lib STATIC ${SOURCE_FILES_STATIC_LIB})
target_include_directories(iz_2_static_lib PUBLIC include)

#------------------------end-static-lib---------------------


add_executable(iz_2 ${ALL_SOURCE_FILES})

target_link_libraries(iz_2 iz_2_static_lib)