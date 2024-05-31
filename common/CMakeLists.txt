cmake_minimum_required(VERSION 3.5)
project(CommonLib
    VERSION 1.0.0
    DESCRIPTION "a library for common functions"
    LANGUAGES C)

SET(SOURCES
    src/common.c
    src/permute.c
    src/singly_linked_list.c
    src/sort.c)

add_library(common STATIC ${SOURCES})
target_include_directories(common PRIVATE include)
