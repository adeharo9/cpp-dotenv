#----------------------- LIBRARY CONFIGURATION --------------------------------

set(LISTENERS_LIB listeners CACHE INTERNAL "")
set(LISTENERS_SRC
    PairsListener.cpp
    PairsListener.h
)

add_library(${LISTENERS_LIB} ${LISTENERS_SRC})

target_link_libraries(${LISTENERS_LIB}
    ${DOTENV_GENERATED_LIB}
    ${STRUCTURES_LIB}
)

target_include_directories(${LISTENERS_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${LISTENERS_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${LISTENERS_LIB} PRIVATE
        -O3
    )
endif()
