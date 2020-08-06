#----------------------- LIBRARY CONFIGURATION --------------------------------

set(LINE_GENERATED_LIB line_generated CACHE INTERNAL "")
set(LINE_GENERATED_SRC
    LineBaseListener.cpp
    LineBaseListener.h
    LineLexer.cpp
    LineLexer.h
    LineListener.cpp
    LineListener.h
    LineParser.cpp
    LineParser.h
)

add_library(${LINE_GENERATED_LIB} ${LINE_GENERATED_SRC})

target_link_libraries(${LINE_GENERATED_LIB}
    ${ANTLR4_CPP_RUNTIME}
)

target_include_directories(${LINE_GENERATED_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${LINE_GENERATED_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${LINE_GENERATED_LIB} PRIVATE
        -w -O3
    )
endif()
