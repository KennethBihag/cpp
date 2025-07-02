cmake_minimum_required(VERSION 3.5)
project(CommonLib
    VERSION 1.0.0
    DESCRIPTION "a library for common functions"
    LANGUAGES C CXX)

SET(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_C_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(SOURCES
    src/colored_console.cpp
    src/common.c src/common.cpp
    src/logger.cpp
    src/permute.c
    src/singly_linked_list.c
    src/sort.c
    src/tests.c)

OPTION(RELBUILD "Release or debug?" ON)
if(RELBUILD)
    message("Building for release")
    SET(CMAKE_BUILD_TYPE Release)
    add_library(common SHARED ${SOURCES})
    target_compile_definitions(common PUBLIC SHARED)
    target_compile_definitions(common PRIVATE EXP_BUILD)
else()
    message(("Building for debug"))
    SET(CMAKE_BUILD_TYPE Debug)
    add_library(common STATIC ${SOURCES})
    target_compile_definitions(common PUBLIC "COMMON_API=")
endif(RELBUILD)

target_include_directories(common PUBLIC include)

add_executable(common.test src/main.cpp)
target_link_libraries(common.test PRIVATE common)

set_target_properties(common PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib/static
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib/shared
)

set_target_properties(common.test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin
)