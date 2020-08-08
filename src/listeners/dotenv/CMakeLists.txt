#----------------------- LIBRARY CONFIGURATION --------------------------------

set(DOTENV_LISTENERS_LIB dotenv_listeners CACHE INTERNAL "")
set(DOTENV_LISTENERS_SRC
    CheckerListener.cpp
    CheckerListener.h
    SymbolsListener.cpp
    SymbolsListener.h
)

add_library(${DOTENV_LISTENERS_LIB} ${DOTENV_LISTENERS_SRC})

target_link_libraries(${DOTENV_LISTENERS_LIB}
    ${DOTENV_GENERATED_LIB}
    ${ENVIRON_LIB}
    ${ERRORS_LIB}
    ${STRUCTURES_LIB}
)

target_include_directories(${DOTENV_LISTENERS_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${DOTENV_LISTENERS_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${DOTENV_LISTENERS_LIB} PRIVATE
        -O3
    )
endif()
