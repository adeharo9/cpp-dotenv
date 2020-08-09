#----------------------- LIBRARY CONFIGURATION --------------------------------

set(STRUCTURES_LIB structures CACHE INTERNAL "")
set(STRUCTURES_SRC
    ReferencesTable.cpp
    ReferencesTable.h
    ReplaceStack.cpp
    ReplaceStack.h
    SymbolsTable.cpp
    SymbolsTable.h
    TreeDecorations.cpp
    TreeDecorations.h
)

add_library(${STRUCTURES_LIB} ${STRUCTURES_SRC})

target_link_libraries(${STRUCTURES_LIB}
    ${ANTLR4_CPP_RUNTIME}
)

target_include_directories(${STRUCTURES_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${STRUCTURES_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${STRUCTURES_LIB} PRIVATE
        -O3
    )
endif()
