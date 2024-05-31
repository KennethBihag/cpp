cmake_minimum_required(VERSION 3.5)
project(Profiler
    VERSION 1.0.0
    DESCRIPTION "Library to profile functions"
    LANGUAGES C CXX)

include_directories(
    ../common/include
    ../)

set(C_STANDARD_REQUIRED ON)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(common STATIC
    ../common/src/common.c
    ../common/src/permute.c
    ../common/src/singly_linked_list.c
    ../common/src/sort.c)
# target_compile_features(common PUBLIC c_std_11)

add_definitions(-DNO_COUT_RDIR)
aux_source_directory(src SOURCES)
add_executable(profiler
    ${SOURCES}
)
target_include_directories(profiler PRIVATE include)
# target_compile_features(profiler PRIVATE cxx_std_17)
target_link_libraries(profiler PUBLIC common)
