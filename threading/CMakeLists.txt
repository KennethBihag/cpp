cmake_minimum_required(VERSION 3.5)
project(Threading
    VERSION 1.0.0
    DESCRIPTION "Library for threading functions"
    LANGUAGES C)

aux_source_directory(src SOURCES)
add_definitions(-DBUILD_MAIN)

add_executable(threading_app
    ${SOURCES}
)
target_compile_features(threading_app PRIVATE c_std_11)
target_include_directories(threading_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)