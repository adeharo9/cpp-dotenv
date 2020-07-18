#----------------------- PROJECT CONFIGURATION -------------------------
cmake_minimum_required(VERSION 3.10)
project(cpp-dotenv VERSION 0.3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#----------------------- LIBRARY CONFIGURATION -------------------------

set(CPP_DOTENV_LIB cpp_dotenv CACHE INTERNAL "")
set(CPP_DOTENV_SRC
    dotenv.h
)

add_library(${CPP_DOTENV_LIB} ${CPP_DOTENV_SRC})
set_target_properties(${CPP_DOTENV_LIB} PROPERTIES
    LINKER_LANGUAGE CXX
)

target_include_directories(${CPP_DOTENV_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
