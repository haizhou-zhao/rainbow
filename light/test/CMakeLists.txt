cmake_minimum_required(VERSION 3.10)
project(light_test)

file(GLOB_RECURSE LIGHT_TEST_SOURCES "*.cpp")

add_executable(light_test ${LIGHT_TEST_SOURCES})

# Link GoogleTest
target_link_libraries(light_test light gtest_main gmock gmock_main)

# Add test to CTest
include(GoogleTest)
gtest_discover_tests(light_test)
