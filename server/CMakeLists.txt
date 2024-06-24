cmake_minimum_required(VERSION 3.5)
project(Server
    VERSION 1.0.0
    DESCRIPTION "A server in C"
    LANGUAGES C)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

option(RELEASE "Release build or debug?" ON)
if(RELEASE)
    set(DBGB -O3)
else()
    set(DBGB -ggdb)
endif()

aux_source_directory(src SRVSRC)
add_executable(server ${SRVSRC})
target_include_directories(server PRIVATE include)
if("$ENV{OS}" STREQUAL "Windows_NT")
    target_compile_definitions(server PRIVATE _WIN32)
    target_compile_options(server PRIVATE -lws2_32 ${DBGB})
else()
    target_compile_options(server PRIVATE ${DBGB})
endif()
# target_compile_options(server PRIVATE -Wno-write-strings)
# target_compile_definitions(server PRIVATE MY_DEF)