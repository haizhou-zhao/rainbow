project(bridge)

add_subdirectory(test)
add_library(bridge private/Catalog.cpp private/InMemoryCatalog.cpp private/SqlContext.cpp)
target_include_directories(bridge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
