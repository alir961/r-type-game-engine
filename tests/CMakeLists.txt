# Unit tests for the engine core (ECS, tools). Standalone: no SFML / vcpkg needed.
#   cmake -S tests -B build/tests && cmake --build build/tests && ctest --test-dir build/tests
cmake_minimum_required(VERSION 3.20)
project(rtype_engine_tests CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

set(ENGINE ${CMAKE_CURRENT_SOURCE_DIR}/../engine)

add_executable(engine_tests
    test_ecs.cpp
    test_tools.cpp
    ${ENGINE}/src/tools/Split.cpp
    ${ENGINE}/src/tools/NumberUtilities.cpp
)
target_include_directories(engine_tests PRIVATE ${ENGINE}/include ${ENGINE}/include/engine)
target_link_libraries(engine_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(engine_tests)
