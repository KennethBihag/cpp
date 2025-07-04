cmake_minimum_required(VERSION 3.5)
project(CNetworking
    VERSION 1.0.0
    DESCRIPTION "Cross platform networing codes"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(include S:/cpp/common/include)
set(LIBSRC lib/networking.cpp lib/interfaces.cpp lib/socket.cpp lib/socket_factory.cpp lib/connection.cpp)
add_library(network SHARED ${LIBSRC} )
add_executable(server src/server.cpp)
add_executable(client src/client.cpp)
add_executable(network.test src/test.cpp)
# set(COMPILE_OPTIONS "-tae")
target_compile_options(network PUBLIC "-Wall" )
# target_compile_options(server PRIVATE "-Wall" )
# target_compile_options(client PRIVATE "-Wall" )

if("$ENV{DESKTOP_SESSION}" STREQUAL "ubuntu")
    message("Building for Ubuntu")
else()
    message("Building for Windows")
    target_link_libraries(network PUBLIC ws2_32 iphlpapi)
endif()

# find_library(CMN_LIB NAMES libcommon PATHS S:/cpp/lib/ )
add_library(common SHARED IMPORTED)
set_target_properties(common
    PROPERTIES
        IMPORTED_IMPLIB S:/cpp/lib/static/libcommon.dll.a
        IMPORTED_LOCATION S:/cpp/lib/shared/libcommon.dll
)
target_compile_definitions(common INTERFACE SHARED)

target_link_libraries(network PUBLIC common)
target_link_libraries(server PRIVATE network)
target_link_libraries(client PRIVATE network)
target_link_libraries(network.test PRIVATE network)

set(CMAKE_BUILD_TYPE Debug)

set_target_properties(network
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY S:/cpp/lib/shared
        ARCHIVE_OUTPUT_DIRECTORY S:/cpp/lib/static
)
set_target_properties(server client network.test
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY S:/cpp/bin
)

