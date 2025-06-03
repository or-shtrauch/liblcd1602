cmake_minimum_required(VERSION 3.10)

project(lcd1602_p)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES src/*.cpp)

add_executable(lcd ${SOURCES} main.cpp)

target_include_directories(lcd PUBLIC include)