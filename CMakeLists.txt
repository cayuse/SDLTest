cmake_minimum_required(VERSION 3.3)
project(SDLTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    res/ship_art/blueshuttlenoweps.png
    res/ship_art/fighterspr.png
    res/ship_art/speedship.png
    src/cleanup.h
    src/res_path.h
    src/SDLTest.cpp
    src/Ship.cpp
    src/Ship.h
    src/Timer.cpp
    src/Timer.h
    Makefile
    notes.txt
    README.md)

add_executable(SDLTest ${SOURCE_FILES})