cmake_minimum_required(VERSION 3.0)
project(antlr4-cpp-runtime VERSION 4.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#------------------- COMPILATION FLAGS ----------------------------------------

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "")
    string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
else()
    set(CMAKE_BUILD_TYPE DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O0")
endif()
message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")

#------------------- SUBDIRECTORY ADDITION ------------------------------------

add_subdirectory(runtime)
