add_library(ui STATIC
    UI.cpp
    UI.h
)

target_include_directories(ui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}         # consumers include "UI.h"
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/core        # UI.cpp includes Task.h, TaskList.h
)

# ui depends on utils for Date, String.util, etc.
target_link_libraries(ui
    PUBLIC
        utils
)

target_set_warnings(ui PRIVATE)
