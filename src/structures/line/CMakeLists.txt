#----------------------- LIBRARY CONFIGURATION --------------------------------

set(LINE_STRUCTURES_LIB line_structures CACHE INTERNAL "")
set(LINE_STRUCTURES_SRC
    SymbolsTable.cpp
    SymbolsTable.h
)

add_library(${LINE_STRUCTURES_LIB} ${LINE_STRUCTURES_SRC})

target_include_directories(${LINE_STRUCTURES_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${LINE_STRUCTURES_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${LINE_STRUCTURES_LIB} PRIVATE
        -O3
    )
endif()
