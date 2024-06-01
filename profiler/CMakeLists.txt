cmake_minimum_required(VERSION 3.5)
project(Profiler
    VERSION 1.0.0
    DESCRIPTION "Library to profile functions"
    LANGUAGES CXX)

include_directories(
    ../common/include
    ../)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

find_library(CMNLIB common ../lib)

add_definitions(-DNO_COUT_RDIR)
aux_source_directory(src SOURCES)
add_executable(profiler
    ${SOURCES}
)
target_include_directories(profiler PRIVATE include)
target_link_libraries(profiler PUBLIC ${CMNLIB})
