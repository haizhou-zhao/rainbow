project(bridge)

add_library(bridge private/Catalog.cpp private/InMemoryCatalog.cpp private/SqlContext.cpp)
target_include_directories(bridge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
target_include_directories(bridge PUBLIC ${CMAKE_SOURCE_DIR}/light/public)
target_link_libraries(bridge light)
