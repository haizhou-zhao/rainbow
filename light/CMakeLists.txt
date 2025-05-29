project(light)

add_subdirectory(test)
add_library(light private/Rule.cpp private/SqlPlan.cpp private/TreeNode.cpp)
target_include_directories(light PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
