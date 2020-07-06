cmake_minimum_required(VERSION 3.7)

#add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
set(CMAKE_BUILD_TYPE Debug)

project(VIRUS)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
INCLUDE(FindPkgConfig)

find_package(OpenCV 4.1 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_DIRS} ${OpenCV_INCLUDE_DIRS} src)
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

add_executable(Virus src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/entity.cpp src/tracking.cpp)

target_link_libraries(Virus ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}  ${OpenCV_LIBRARIES})

