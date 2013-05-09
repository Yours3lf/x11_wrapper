cmake_minimum_required(VERSION 2.8)

project(x11_wrapper)

add_subdirectory(x11)

add_executable(x11_wrapper main.cpp)

target_link_libraries(x11_wrapper x11)