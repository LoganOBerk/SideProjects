add_library(utils STATIC
    Math.util.cpp
    Math.util.h
    String.util.cpp
    String.util.h
)

target_include_directories(utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}   
)

target_set_warnings(utils PRIVATE)
