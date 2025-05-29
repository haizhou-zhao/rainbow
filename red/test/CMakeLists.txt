cmake_minimum_required(VERSION 3.10)
project(red_test)

file(GLOB_RECURSE RED_TEST_SOURCES "*.cpp")

add_executable(red_test ${RED_TEST_SOURCES})

# Link GoogleTest and other dependencies
target_link_libraries(red_test red light gtest_main gmock gmock_main)

# Add test to CTest
include(GoogleTest)
gtest_discover_tests(red_test)
