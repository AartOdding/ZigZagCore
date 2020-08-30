cmake_minimum_required(VERSION 3.1)

add_library(sol2 INTERFACE)
target_include_directories(sol2 "${CMAKE_CURRENT_LIST_DIR}/sol2/include")
