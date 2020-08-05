#----------------------- LIBRARY CONFIGURATION --------------------------------

set(ENVIRON_LIB environ CACHE INTERNAL "")
set(ENVIRON_SRC
    environ.cpp
    environ.h
)

add_library(${ENVIRON_LIB} ${ENVIRON_SRC})

target_include_directories(${ENVIRON_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${ENVIRON_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${ENVIRON_LIB} PRIVATE
        -O3
    )
endif()
