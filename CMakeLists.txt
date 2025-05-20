# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

project(rainbow)

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
