# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rainbow)

# Formatting cmake list files are manual invoking
# cmake-format with
# find <directory> -name "CMakeLists.txt" -o -name "*.cmake" | xargs -I {} cmake-format {}
# https://cmake-format.readthedocs.io/en/latest/installation.html
# formatting C++ sources are automated but
# requiring formatter utilities to be installed
# https://clang.llvm.org/docs/ClangFormat.html
find_program(CLANG_FORMAT clang-format REQUIRED)

file(GLOB_RECURSE CXX_SOURCES 
    "**/public/*.h"
    "**/private/*.cpp"
    "**/test/*.cpp"
)

add_custom_target(clangformat
    COMMAND ${CLANG_FORMAT} -i -style=file ${CXX_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Formatting code with clang-format"
    VERBATIM
)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# project light includes many common utilities and internal data structure
# which is a common dependencies of the rest of sub-modules
add_subdirectory(light)
# project bridge is the Catalog
add_subdirectory(bridge)
# project red is the SQL/User Input Parser
add_subdirectory(red)
# project orange is the Analyzer
add_subdirectory(orange)

add_executable(rainbow main.cpp)
target_link_libraries(rainbow red orange bridge)
get_target_property(RED_INCLUDES red INCLUDE_DIRECTORIES)
get_target_property(ORANGE_INCLUDES orange INCLUDE_DIRECTORIES)
get_target_property(BRIDGE_INCLUDES bridge INCLUDE_DIRECTORIES)
target_include_directories(rainbow PUBLIC "${RED_INCLUDES} ${ORANGE_INCLUDES} ${BRIDGE_INCLUDES}")

add_dependencies(rainbow clangformat)
