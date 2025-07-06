cmake_minimum_required(VERSION 3.5)
project(MyCppProject
    VERSION 1.0.0
    DESCRIPTION "Just some practice codes"
)

add_subdirectory(common)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

install(TARGETS common
    ARCHIVE DESTINATION lib/static
    LIBRARY DESTINATION lib/shared
    RUNTIME DESTINATION lib/shared
)

install(TARGETS test_common
    RUNTIME DESTINATION bin
)

include(mkdir.cmake)