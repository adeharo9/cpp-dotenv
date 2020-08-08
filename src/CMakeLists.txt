#------------------- SUBDIRECTORY ADDITION ------------------------------------

add_subdirectory(common)
add_subdirectory(structures)
add_subdirectory(listeners)

#----------------------- LIBRARY CONFIGURATION --------------------------------

set(PARSER_LIB parser CACHE INTERNAL "")
set(PARSER_SRC
    Parser.cpp
    Parser.h
)

add_library(${PARSER_LIB} ${PARSER_SRC})

target_link_libraries(${PARSER_LIB}
    ${ANTLR4_CPP_RUNTIME}
    ${DOTENV_GENERATED_LIB}
    ${DOTENV_LISTENERS_LIB}
    ${ENVIRON_LIB}
    ${ERRORS_LIB}
    ${LINE_GENERATED_LIB}
    ${LINE_LISTENERS_LIB}
    ${STRUCTURES_LIB}
)

target_include_directories(${PARSER_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${PARSER_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${PARSER_LIB} PRIVATE
        -O3
    )
endif()
