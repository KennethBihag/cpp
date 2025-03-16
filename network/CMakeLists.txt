cmake_minimum_required(VERSION 3.5)
project(CNetworking
    VERSION 1.0.0
    DESCRIPTION "Cross platform networing codes"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(network network.cpp other.cpp)

if("$ENV{DESKTOP_SESSION}" STREQUAL "ubuntu")
    message("Building for Ubuntu")
else()
    message("Building for Windows")
    # target_compile_options(network PRIVATE "-lws2_32" "-liphlpapi")
    target_link_libraries(network PRIVATE ws2_32 iphlpapi)
endif()

target_compile_options(network PRIVATE "-Wall" "-Werror" "-ggdb")
