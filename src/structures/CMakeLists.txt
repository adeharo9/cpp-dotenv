#----------------------- LIBRARY CONFIGURATION --------------------------------

set(STRUCTURES_LIB structures CACHE INTERNAL "")
set(STRUCTURES_SRC
    PairsTable.h
)

add_library(${STRUCTURES_LIB} ${STRUCTURES_SRC})
set_target_properties(${STRUCTURES_LIB} PROPERTIES
    LINKER_LANGUAGE CXX
)

target_include_directories(${STRUCTURES_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
