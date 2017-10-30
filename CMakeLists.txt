cmake_minimum_required(VERSION 3.0)
project(TerminalFighter)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/")

include(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

find_package(SDL2_ttf REQUIRED)
find_package(glog 0.3.5 REQUIRED)
find_package(yaml-cpp REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -g")
add_subdirectory(src/Engine)
add_subdirectory(src/TerminalFighter)
add_subdirectory(test)
