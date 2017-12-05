cmake_minimum_required(VERSION 3.2)
project(MaSimHpc)

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_SUBDIRECTORY(src)

################################
# Testing
################################
# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(BUILD_TESTS "Build all tests." OFF) # Makes boolean 'test' available.
if (BUILD_TESTS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage")
    ADD_SUBDIRECTORY(${EXT_PROJECTS_DIR}/googletest)
    enable_testing()
    ADD_SUBDIRECTORY(test)

endif ()

