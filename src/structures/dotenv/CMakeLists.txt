#----------------------- LIBRARY CONFIGURATION --------------------------------

set(DOTENV_STRUCTURES_LIB dotenv_structures CACHE INTERNAL "")
set(DOTENV_STRUCTURES_SRC
    PairsTable.h
)

add_library(${DOTENV_STRUCTURES_LIB} ${DOTENV_STRUCTURES_SRC})
set_target_properties(${DOTENV_STRUCTURES_LIB} PROPERTIES
    LINKER_LANGUAGE CXX
)

target_include_directories(${DOTENV_STRUCTURES_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
