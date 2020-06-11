cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

project(Pac-Man)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

# Find all executables
#file(GLOB project_SRCS src/*.cpp src/*.h)
#add_executable(PacMan ${project_SRCS})
add_executable(PacMan src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/pacman.cpp)


#string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(PacMan ${SDL2_LIBRARIES})