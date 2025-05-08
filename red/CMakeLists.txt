project(red)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/3rdparty/cmake/antlr4)
# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)

# Specify the version of the antlr4 library needed for this project.
# By default the latest version of antlr4 will be used.  You can specify a
# specific, stable version by setting a repository tag value or a link
# to a zip file containing the libary source.
# set(ANTLR4_TAG 4.13.2)
# set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/4.13.2.zip)

# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antlr4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})
link_directories( ${ANTLR4CPP_LIBS} )

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/3rdparty/bin/antlr4/antlr-4.13.2-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(SqlBaseLexer ${PROJECT_SOURCE_DIR}/grammar/SqlBaseLexer.g4
             LEXER
             PACKAGE sqlgrammar)
antlr_target(SqlBaseParser ${PROJECT_SOURCE_DIR}/grammar/SqlBaseParser.g4
             PARSER
             PACKAGE sqlgrammar
             DEPENDS_ANTLR SqlBaseLexer
             COMPILE_FLAGS -lib ${ANTLR_SqlBaseLexer_OUTPUT_DIR}
             VISITOR)

# include generated files in project environment
include_directories(${ANTLR_SqlBaseLexer_OUTPUT_DIR})
include_directories(${ANTLR_SqlBaseParser_OUTPUT_DIR})

add_library(red private/AstBuilder.cpp private/SqlPlan.cpp
            ${ANTLR_SqlBaseLexer_CXX_OUTPUTS}
            ${ANTLR_SqlBaseParser_CXX_OUTPUTS})
target_link_libraries(red antlr4_static)
target_include_directories(red PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
