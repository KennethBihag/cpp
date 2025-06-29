cmake_minimum_required(VERSION 3.5)
project(MyCppProject
    VERSION 1.0.0
    DESCRIPTION "Just some practice codes"
    LANGUAGES C CXX)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    "."
    "common/include"
    "threading/include"
    "leetcode/include"
    "profiler/include")

option(RELEASE "Release build or debug?" ON)
if(RELEASE)
    set(LIBTYPE SHARED)
    set(CMAKE_BUILD_TYPE Release)
else()
    set(LIBTYPE STATIC)
    set(CMAKE_BUILD_TYPE Debug)
endif()

aux_source_directory(common/src CMNSRC)
set_source_files_properties(${CMNSRC} LANGUAGE CXX)
add_library(common ${LIBTYPE} ${CMNSRC})
target_compile_definitions(common PUBLIC EXP_BUILD)

aux_source_directory(leetcode/src LTCSRC)
add_library(leetcodel ${LIBTYPE} ${LTCSRC})
target_compile_definitions(leetcodel PUBLIC CODEIUM_GEN BUILD_LIB)
target_compile_options(leetcodel PRIVATE -Wno-write-strings)

target_link_libraries(leetcodel PUBLIC common)

aux_source_directory(threading/src TRDSRC)
add_library(threading ${LIBTYPE} ${TRDSRC})


add_executable(leetcode ${LTCSRC})
target_link_libraries(leetcode PUBLIC common threading)
target_compile_definitions(leetcode PRIVATE CODEIUM_GEN ALL_CHALLENGES)
target_compile_options(leetcode PRIVATE -Wno-write-strings)


aux_source_directory(profiler/src PFLSRC)
add_executable(profiler ${PFLSRC})
target_link_libraries(profiler PUBLIC common)
if("$ENV{OS}" STREQUAL "Windows_NT" AND RELEASE)
    message("In release mode in Windows")
    target_compile_options(profiler PRIVATE -O0)
else()
    message("Not release mode in Windows")

endif()

add_executable(profiler2 ${PFLSRC})
target_link_libraries(profiler2 PUBLIC common leetcodel)
target_compile_definitions(profiler2 PRIVATE STD_THREAD)


add_executable(threadingexe ${TRDSRC})
target_compile_definitions(threadingexe PRIVATE BUILD_MAIN)



aux_source_directory(testapp/src TSTSRC)
add_executable(testapp ${TSTSRC})
target_link_libraries(testapp PUBLIC common)
target_compile_options(testapp PRIVATE -Wno-pointer-arith)

