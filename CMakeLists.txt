cmake_minimum_required(VERSION 3.10.2)
project(ragemash)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp)

add_executable(ragemash ${SOURCE_FILES})
target_link_libraries(ragemash ${SDL2_LIBRARY})
