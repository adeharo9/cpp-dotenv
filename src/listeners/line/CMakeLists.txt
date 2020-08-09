#----------------------- LIBRARY CONFIGURATION --------------------------------

set(LINE_LISTENERS_LIB line_listeners CACHE INTERNAL "")
set(LINE_LISTENERS_SRC
    ExpanderListener.cpp
    ExpanderListener.h
    ExternalResolverListener.cpp
    ExternalResolverListener.h
    ReferencesListener.cpp
    ReferencesListener.h
    LocalResolverListener.cpp
    LocalResolverListener.h
    UndefinedListener.cpp
    UndefinedListener.h
    UnresolvableListener.cpp
    UnresolvableListener.h
)

add_library(${LINE_LISTENERS_LIB} ${LINE_LISTENERS_SRC})

target_link_libraries(${LINE_LISTENERS_LIB}
    ${ENVIRON_LIB}
    ${ERRORS_LIB}
    ${ESCAPE_LIB}
    ${LINE_GENERATED_LIB}
    ${STRUCTURES_LIB}
)

target_include_directories(${LINE_LISTENERS_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(${LINE_LISTENERS_LIB} PRIVATE
        -g -Wall -O0
    )
else()
    target_compile_options(${LINE_LISTENERS_LIB} PRIVATE
        -O3
    )
endif()
