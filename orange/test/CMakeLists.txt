cmake_minimum_required(VERSION 3.10)
project(orange_test)

file(GLOB_RECURSE ORANGE_TEST_SOURCES "*.cpp")

add_executable(orange_test ${ORANGE_TEST_SOURCES})

# Link GoogleTest
target_link_libraries(orange_test orange gtest_main gmock gmock_main)

# Add test to CTest
include(GoogleTest)
gtest_discover_tests(orange_test)
