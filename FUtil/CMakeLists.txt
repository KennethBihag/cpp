cmake_minimum_required(VERSION 3.5)
project(FileUtility
    VERSION 1.0.0
    DESCRIPTION "Utility to modify files"
    LANGUAGES CXX)

include_directories(include)
aux_source_directory(src SOURCES)

add_executable(FUtil
    ${SOURCES}
)
target_compile_features(FUtil PRIVATE cxx_std_14)