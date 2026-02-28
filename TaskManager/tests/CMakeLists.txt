include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE GTest::gtest_main core)
target_compile_features(tests PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(tests)
