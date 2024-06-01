cmake_minimum_required(VERSION 3.5)
project(MyCppProject
    VERSION 1.0.0
    DESCRIPTION "Just some practice codes"
    LANGUAGES C CXX)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

include_directories(
    "."
    "common/include"
    "threading/include"
    "leetcode/include"
    "profiler/include")

aux_source_directory(common/src CMNSRC)
add_library(common SHARED ${CMNSRC})

aux_source_directory(leetcode/src LTCSRC)
add_library(leetcodel SHARED ${LTCSRC})
target_compile_definitions(leetcodel PUBLIC CODEIUM_GEN BUILD_LIB)
target_compile_options(leetcodel PUBLIC -Wno-write-strings)
target_compile_features(leetcodel PUBLIC cxx_std_17)
target_link_libraries(leetcodel PUBLIC common)

aux_source_directory(threading/src TRDSRC)
add_library(threading SHARED ${TRDSRC})

add_executable(leetcode ${LTCSRC})
target_link_libraries(leetcode PUBLIC common threading)
target_compile_definitions(leetcode PUBLIC CODEIUM_GEN ALL_CHALLENGES)
target_compile_options(leetcode PUBLIC -Wno-write-strings)
target_compile_features(leetcode PUBLIC cxx_std_17)

aux_source_directory(profiler/src PFLSRC)
add_executable(profiler ${PFLSRC})
target_link_libraries(profiler PUBLIC common)
# target_compile_definitions(profiler PUBLIC NO_COUT_RDIR)
target_compile_features(profiler PUBLIC cxx_std_17)

add_executable(profiler2 ${PFLSRC})
target_link_libraries(profiler2 PUBLIC common leetcodel)
target_compile_definitions(profiler2 PUBLIC STD_THREAD)
target_compile_features(profiler2 PUBLIC cxx_std_17)

add_executable(threadingexe ${TRDSRC})
target_compile_definitions(threadingexe PUBLIC BUILD_MAIN)

aux_source_directory(testapp/src TSTSRC)
add_executable(testapp ${TSTSRC})
target_link_libraries(testapp PUBLIC common)
target_compile_options(testapp PUBLIC -Wno-pointer-arith)