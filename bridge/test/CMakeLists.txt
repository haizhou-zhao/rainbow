cmake_minimum_required(VERSION 3.10)
project(bridge_test)

file(GLOB_RECURSE BRIDGE_TEST_SOURCES "*.cpp")

add_executable(bridge_test ${BRIDGE_TEST_SOURCES})

# Link GoogleTest
target_link_libraries(bridge_test bridge gtest_main)

# Add test to CTest
include(GoogleTest)
gtest_discover_tests(bridge_test)
