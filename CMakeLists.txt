cmake_minimum_required(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(TagSystem)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)