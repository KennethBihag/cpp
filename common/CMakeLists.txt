cmake_minimum_required(VERSION 3.5)
project(CommonLib
    VERSION 1.0.0
    DESCRIPTION "a library for common functions"
    LANGUAGES C CXX)

SET(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_C_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src LIB_SRCS)
set(TST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/tests.c ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
remove(LIB_SRCS ${TST_SRCS})

if(CMAKE_BUILD_TYPE MATCHES Release|RelWithDebInfo)
    message("Building for ${CMAKE_BUILD_TYPE}")
    add_library(common SHARED ${LIB_SRCS})
    target_compile_definitions(common PUBLIC SHARED)
    target_compile_definitions(common PRIVATE EXP_BUILD)
    set(BUILD_RPATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/shared)
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Building for debug")
    add_library(common STATIC ${LIB_SRCS})
    target_compile_definitions(common PUBLIC "COMMON_API=")
endif()
add_executable(test_common ${TST_SRCS})

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(test_common PRIVATE common)

include(${CMAKE_CURRENT_SOURCE_DIR}/../mkdir.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../setlibdirs.cmake)
SetLibDirs(common)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
