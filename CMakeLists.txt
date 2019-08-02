cmake_minimum_required(VERSION 3.1)
project(lib-sql-text)


if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    find_package( lib-sql )
endif()

find_package(Catch2 REQUIRED)

# Boost
find_package( Boost 1.61.0 COMPONENTS filesystem system )
include_directories( ${Boost_INCLUDE_DIR} )


# Compiler options
# Clang maximum template depth seems to be 256
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ftemplate-depth-750" )
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ferror-limit=1000" )

# SQL grammar library
add_library(sql_text INTERFACE)
target_include_directories(sql_text INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sql_text INTERFACE sql)
export(TARGETS sql_text FILE sql_textConfig.cmake)
export(PACKAGE sql_text)


# SQL parser library
set(LIBRARY_SOURCE_FILES
        src/sql/text/parser.cpp)

add_library(sql_text_parser SHARED ${LIBRARY_SOURCE_FILES})
target_link_libraries(sql_text_parser sql)
target_include_directories(sql_text_parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
export(TARGETS sql_text_parser FILE sql_text_parserConfig.cmake)
export(PACKAGE sql_text_parser)

set_property(TARGET sql_text_parser PROPERTY CXX_STANDARD 14)
set_property(TARGET sql_text_parser PROPERTY CXX_STANDARD_REQUIRED ON)


# Catch
enable_testing(true)
set(TEST_ENABLED true)


# Tests
add_subdirectory(test)
