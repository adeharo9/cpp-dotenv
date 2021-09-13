#----------------------- PROJECT CONFIGURATION --------------------------------
cmake_minimum_required(VERSION 3.10)

project(cpp-dotenv
        VERSION 1.0.0
        DESCRIPTION "Library to load environment variables from .env files for C++ projects."
        )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DOTENV_SHARED_LIB "Build CPP-DOTENV as a shared library" NO)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE RELEASE)
else()
    string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
endif()
message(STATUS "Building CPP-DOTENV in ${CMAKE_BUILD_TYPE} mode")

find_package(PkgConfig REQUIRED)

#------------------- SUBDIRECTORY ADDITION ------------------------------------

add_subdirectory(common)
add_subdirectory(src)

#----------------------- LIBRARY CONFIGURATION --------------------------------

set(CPP_DOTENV cpp-dotenv CACHE INTERNAL "")
set(CPP_DOTENV_SRC
    src/dotenv.cpp
    include/dotenv.h
)
if(DOTENV_SHARED_LIB)
    add_library(${CPP_DOTENV} SHARED ${CPP_DOTENV_SRC})
    message(STATUS "Building as shared library")
else()
    add_library(${CPP_DOTENV} ${CPP_DOTENV_SRC})
    message(STATUS "Building as static library")
endif()

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

#include(GNUInstallDirs)

#----------------------- PKG CONFIGURATION --------------------------------
message(STATUS "Package CPP-DOTENV for ${CMAKE_BUILD_TYPE} version ${PROJECT_VERSION}")
set(TARGET1 ${CPP_DOTENV})

# Generate pkg-config file
configure_file(./cpp-dotenv.pc.in ${PROJECT_BINARY_DIR}/cpp-dotenv.pc @ONLY)


#----------------------- INSTALL --------------------------------
include(GNUInstallDirs)
if(DOTENV_SHARED_LIB)
    install(TARGETS ${CPP_DOTENV} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    install(FILES ${CMAKE_SOURCE_DIR}/include/dotenv.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/)
    install(FILES ${PROJECT_BINARY_DIR}/cpp-dotenv.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif()
