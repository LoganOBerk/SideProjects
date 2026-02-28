add_executable(TaskManager
    Main.cpp
)

# The executable only needs to know about core; the rest propagates transitively.
target_link_libraries(TaskManager
    PRIVATE
        core
)

target_set_warnings(TaskManager PRIVATE)

# Place the built binary in the project root's build output for convenience
set_target_properties(TaskManager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
