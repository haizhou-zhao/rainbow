# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

project(rainbow)

add_subdirectory(red)

add_executable(rainbow main.cpp)
target_link_libraries(rainbow red)
get_target_property(RED_INCLUDES red INCLUDE_DIRECTORIES)
target_include_directories(rainbow PUBLIC "${RED_INCLUDES}")
