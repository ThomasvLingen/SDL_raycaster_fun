cmake_minimum_required(VERSION 3.3)
project(SDL_raycaster_fun)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

set(SOURCE_FILES
    src/alterworldevent.cpp
    src/alterworldevent.h
    src/Game.cpp
    src/Game.h
    src/GameObject.h
    src/Keyboard.cpp
    src/Keyboard.h
    src/main.cpp
    src/player.cpp
    src/player.h
    src/raycasterworld.cpp
    src/raycasterworld.h
    src/vectorutil.cpp
    src/vectorutil.h src/FPSCounter.cpp src/FPSCounter.h src/Color.cpp src/Color.hpp)

add_executable(SDL_raycaster_fun ${SOURCE_FILES})
target_link_libraries(SDL_raycaster_fun ${SDL2_LIBRARY})
target_link_libraries(SDL_raycaster_fun ${SDL2_TTF_LIBRARIES})