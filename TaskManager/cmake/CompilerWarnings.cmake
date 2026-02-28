# cmake/CompilerWarnings.cmake
# Provides a helper function to attach a standard set of compiler warnings
# to any target without polluting global flags.
#
# Usage:
#   target_set_warnings(<target> <PRIVATE|PUBLIC|INTERFACE>)

function(target_set_warnings TARGET VISIBILITY)
    if(MSVC)
        target_compile_options(${TARGET} ${VISIBILITY}
            /W3         # High warning level
            /WX         # Treat warnings as errors
            /permissive-# Enforce standards conformance
        )
    else()
        target_compile_options(${TARGET} ${VISIBILITY}
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
            -Wconversion
            -Wsign-conversion
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
        )
    endif()
endfunction()
