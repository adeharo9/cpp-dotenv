#----------------------- LIBRARY CONFIGURATION --------------------------------

set(ENVIRON_LIB environ CACHE INTERNAL "")
set(ENVIRON_SRC
    environ.h
)

add_library(${ENVIRON_LIB} ${ENVIRON_SRC})
set_target_properties(${ENVIRON_LIB} PROPERTIES
    LINKER_LANGUAGE CXX
)

target_include_directories(${ENVIRON_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
