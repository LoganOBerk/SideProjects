cmake_minimum_required(VERSION 3.21)

project(TaskManager
    VERSION 1.0.0
    DESCRIPTION "A command-line To-do List Manager"
    LANGUAGES CXX
)

# ── Language standard ──────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Build type default ─────────────────────────────────────────────────────────
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Build type not set — defaulting to Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# ── Compiler warnings module ───────────────────────────────────────────────────
include(cmake/CompilerWarnings.cmake)

# ── Subdirectories ─────────────────────────────────────────────────────────────
add_subdirectory(src/utils)
add_subdirectory(src/ui)
add_subdirectory(src/core)
add_subdirectory(src/app)

enable_testing()
add_subdirectory(tests)


