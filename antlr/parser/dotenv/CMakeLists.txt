#----------------------- LIBRARY CONFIGURATION --------------------------------

set(DOTENV_GENERATED_LIB dotenv_generated CACHE INTERNAL "")
set(DOTENV_GENERATED_SRC
    DotenvBaseListener.cpp
    DotenvBaseListener.h
    DotenvLexer.cpp
    DotenvLexer.h
    DotenvListener.cpp
    DotenvListener.h
    DotenvParser.cpp
    DotenvParser.h
)

add_library(${DOTENV_GENERATED_LIB} ${DOTENV_GENERATED_SRC})

target_link_libraries(${DOTENV_GENERATED_LIB}
    ${ANTLR4_CPP_RUNTIME}
)

target_include_directories(${DOTENV_GENERATED_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${DOTENV_GENERATED_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${DOTENV_GENERATED_LIB} PRIVATE
        -w -O3
    )
endif()
