project(orange)

add_library(orange private/Analyzer.cpp private/RuleExecutor.cpp)
target_include_directories(orange PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
target_include_directories(orange PUBLIC ${CMAKE_SOURCE_DIR}/light/public)
target_link_libraries(orange light)
