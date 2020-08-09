#----------------------- PROJECT CONFIGURATION --------------------------------
cmake_minimum_required(VERSION 3.10)
project(cpp-dotenv VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE RELEASE)
else()
    string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
endif()
message(STATUS "Building CPP-DOTENV in ${CMAKE_BUILD_TYPE} mode")

#------------------- SUBDIRECTORY ADDITION ------------------------------------

add_subdirectory(common)
add_subdirectory(src)

#----------------------- LIBRARY CONFIGURATION --------------------------------

set(CPP_DOTENV cpp_dotenv CACHE INTERNAL "")
set(CPP_DOTENV_SRC
    src/dotenv.cpp
    include/dotenv.h
)

add_library(${CPP_DOTENV} ${CPP_DOTENV_SRC})

target_link_libraries(${CPP_DOTENV}
    ${ENVIRON_LIB}
    ${PARSER_LIB}
)

target_include_directories(${CPP_DOTENV} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${CPP_DOTENV} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${CPP_DOTENV} PRIVATE
        -O3
    )
endif()
