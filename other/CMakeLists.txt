cmake_minimum_required(VERSION 3.20.0)
project(MyGUID)
add_library(MyGUID MyGUID.cpp)
#[[ optional install only works for debug config
set_target_properties(MyGUID PROPERTIES PUBLIC_HEADER MyGUID.hpp)
install(TARGETS MyGUID LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION ./
)]]
