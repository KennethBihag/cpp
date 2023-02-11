#[[ run on CLI cmake [--fresh] [-A <WIN32 | WIN64>] -B cmake-build]]

cmake_minimum_required(VERSION 3.20.0)
project(TestGUIDApp)
include_directories(other)

#[[ build as one project both main  and library
add_executable(TestExecutable main.cpp other/MyGUID.cpp)
]]
# build by linking
add_executable(TestExecutable main.cpp)

#[[ build static library first then build executable
target_link_directories(TestExecutable PUBLIC ${CMAKE_SOURCE_DIR}/other/cmake-build)
]]
add_subdirectory(${CMAKE_SOURCE_DIR}/other) #this line to not need build static lib separately from line 13

target_link_libraries(TestExecutable MyGUID)
