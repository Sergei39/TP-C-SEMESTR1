cmake_minimum_required(VERSION 3.6)
project(iz-2)

set(PROJECT_NAME iz-2)
set(CMAKE_CXX_STANDARD 14)

set(ALL_SOURCE_FILES
        main.c
        src/complex_matrix.c
        include/complex_matrix.h
        )

set(UNIT_TESTS
        unit_tests/tests.cpp
        unit_tests/test_main.cpp
        )

#-------------------------static-lib-----------------------
set(STATIC_LIB base_matrix_lib)

set(SOURCE_FILES_STATIC_LIB
        src/naive_matrix.c
        src/matrix_memory.c
        )

set(HEADER_FILES_STATIC_LIB
        include/naive_matrix.h
        include/matrix_memory.h
        )

add_library(${STATIC_LIB} STATIC ${SOURCE_FILES_STATIC_LIB})
target_include_directories(${STATIC_LIB} PUBLIC include)

#------------------------end-static-lib---------------------


#-------------------------dynamic-lib-----------------------
set(DYNAMIC_LIB complex_matrix_lib)

set(SOURCE_FILES_DYNAMIC_LIB
        src/complex_matrix.c
        src/matrix_memory.c
        )

set(HEADER_FILES_DYNAMIC_LIB
        include/complex_matrix.h
        include/matrix_memory.h
        )

add_library(${DYNAMIC_LIB} STATIC ${SOURCE_FILES_DYNAMIC_LIB})
target_include_directories(${DYNAMIC_LIB} PUBLIC include)

#------------------------end-static-lib---------------------


#---------------------------google-tests---------------------------

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
#target_link_libraries(example gtest_main)
#add_test(NAME example_test COMMAND example)

#----------------------------include-test-----------------------------

add_executable(test_naive ${UNIT_TESTS})
target_link_libraries(unit-test gtest gtest_main rt pthread ${STATIC_LIB})

add_executable(test_complex ${UNIT_TESTS})
target_link_libraries(unit-test gtest gtest_main rt pthread ${DYNAMIC_LIB})

#-----------------------------end-google-tests-----------------------------



add_executable(${PROJECT_NAME} ${ALL_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${STATIC_LIB})