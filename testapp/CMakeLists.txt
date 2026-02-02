cmake_minimum_required(VERSION 3.5)
project(TestApplication
    VERSION 1.0.0
    DESCRIPTION "Test program for practice"
    LANGUAGES C CXX
)

aux_source_directory(src SOURCES)
include_directories(./)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../bin)
add_compile_options(/Wall /EHsc)

add_executable(testapp ${SOURCES})