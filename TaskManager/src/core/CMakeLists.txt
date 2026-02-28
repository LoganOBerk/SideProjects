add_library(core STATIC
    Date.cpp
    Date.h
    Task.cpp
    Task.h
    TaskList.cpp
    TaskList.h
    TaskListManager.cpp
    TaskListManager.h
    TaskManagerApp.cpp
    TaskManagerApp.h
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}         # consumers include "TaskManagerApp.h", etc.
        ${CMAKE_SOURCE_DIR}/src/ui          # core headers include "UI.h"
        ${CMAKE_SOURCE_DIR}/src/utils       # core headers include "Date.h", "String.util.h"
)

# core depends on utils (Date, String.util) and ui (UI)
target_link_libraries(core
    PUBLIC
        utils
        ui
)

target_set_warnings(core PRIVATE)
