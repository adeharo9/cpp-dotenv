#----------------------- LIBRARY CONFIGURATION --------------------------------

set(LINE_PARSER_LIB line_parser CACHE INTERNAL "")
set(LINE_PARSER_SRC
    LineBaseListener.cpp
    LineBaseListener.h
    LineLexer.cpp
    LineLexer.h
    LineListener.cpp
    LineListener.h
    LineParser.cpp
    LineParser.h
)

add_library(${LINE_PARSER_LIB} ${LINE_PARSER_SRC})

target_link_libraries(${LINE_PARSER_LIB}
    ${ANTLR4_CPP_RUNTIME}
)

target_include_directories(${LINE_PARSER_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${LINE_PARSER_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${LINE_PARSER_LIB} PRIVATE
        -w -O3
    )
endif()
