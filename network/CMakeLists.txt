cmake_minimum_required(VERSION 3.5)
project(CNetworking
    VERSION 1.0.0
    DESCRIPTION "Cross platform networing codes"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(include ${CMAKE_CURRENT_SOURCE_DIR}/../common/include)
set(LIBSRC lib/networking.cpp lib/interfaces.cpp lib/socket.cpp lib/socket_factory.cpp lib/connection.cpp)
add_library(network SHARED ${LIBSRC} )
add_executable(server src/server.cpp)
add_executable(client src/client.cpp)
add_executable(test_network src/test.cpp)
target_compile_options(network PUBLIC "-Wall" )

if("$ENV{DESKTOP_SESSION}" STREQUAL "ubuntu")
    message("Building for Ubuntu")
else()
    message("Building for Windows")
    target_link_libraries(network PUBLIC ws2_32 iphlpapi)
endif()

add_library(common SHARED IMPORTED)
set_target_properties(common
    PROPERTIES
        IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/../lib/static/libcommon.dll.a
)

target_compile_definitions(network PUBLIC SHARED)

target_link_libraries(network PUBLIC common)
target_link_libraries(server PRIVATE network)
target_link_libraries(client PRIVATE network)
target_link_libraries(test_network PRIVATE network)

include(${CMAKE_CURRENT_SOURCE_DIR}/../mkdir.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../setlibdirs.cmake)
SetLibDirs(network)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib/shared)
install(
    TARGETS network
    RUNTIME DESTINATION ${SHARED_DIR}
    LIBRARY DESTINATION ${SHARED_DIR}
)