cmake_minimum_required(VERSION 3.5)
project(CNetworking
    VERSION 1.0.0
    DESCRIPTION "Cross platform networing codes"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
set(LIBSRC lib/networking.cpp lib/Addr.cpp)
add_library(network ${LIBSRC} )
add_executable(server src/server.cpp)
add_executable(client src/client.cpp)
target_compile_options(network PRIVATE "-Wall" "-Werror" "-Wno-error=misleading-indentation")
target_compile_options(server PRIVATE "-Wall" "-Werror")
target_compile_options(client PRIVATE "-Wall" "-Werror")

if("$ENV{DESKTOP_SESSION}" STREQUAL "ubuntu")
    message("Building for Ubuntu")
else()
    message("Building for Windows")
    target_link_libraries(network PUBLIC ws2_32 iphlpapi)
endif()

target_link_libraries(server PRIVATE network)
target_link_libraries(client PRIVATE network)

set(CMAKE_BUILD_TYPE Debug)


