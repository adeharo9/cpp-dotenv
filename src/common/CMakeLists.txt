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


set(ESCAPE_LIB escape CACHE INTERNAL "")
set(ESCAPE_SRC
    escape.cpp
    escape.h
)

add_library(${ESCAPE_LIB} ${ESCAPE_SRC})

target_link_libraries(${ESCAPE_LIB}
    ${ANTLR4_CPP_RUNTIME}
    ${LOGGER_LIB}
)

target_include_directories(${ESCAPE_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${ESCAPE_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${ESCAPE_LIB} PRIVATE
        -O3
    )
endif()


set(LOGGER_LIB logger CACHE INTERNAL "")
set(LOGGER_SRC
    logger.cpp
    logger.h
)

add_library(${LOGGER_LIB} ${LOGGER_SRC})

target_include_directories(${LOGGER_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${LOGGER_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${LOGGER_LIB} PRIVATE
        -O3
    )
endif()


set(ERRORS_LIB errors CACHE INTERNAL "")
set(ERRORS_SRC
    errors.cpp
    errors.h
)

add_library(${ERRORS_LIB} ${ERRORS_SRC})

target_link_libraries(${ERRORS_LIB}
    ${ANTLR4_CPP_RUNTIME}
    ${LOGGER_LIB}
)

target_include_directories(${ERRORS_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${ERRORS_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${ERRORS_LIB} PRIVATE
        -O3
    )
endif()
