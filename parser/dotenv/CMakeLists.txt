#----------------------- LIBRARY CONFIGURATION --------------------------------

set(DOTENV_PARSER_LIB dotenv_parser CACHE INTERNAL "")
set(DOTENV_PARSER_SRC
    DotenvBaseListener.cpp
    DotenvBaseListener.h
    DotenvLexer.cpp
    DotenvLexer.h
    DotenvListener.cpp
    DotenvListener.h
    DotenvParser.cpp
    DotenvParser.h
)

add_library(${DOTENV_PARSER_LIB} ${DOTENV_PARSER_SRC})

target_link_libraries(${DOTENV_PARSER_LIB}
    ${ANTLR4_CPP_RUNTIME}
)

target_include_directories(${DOTENV_PARSER_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
