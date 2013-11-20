cmake_minimum_required(VERSION 2.8.8)

project(Paddlemonium)

include(../Forge/ForgeDependencies.cmake)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(Game_SOURCES
  Input/InGameProcessor.cpp
  State/InGame.cpp
  State/Menu.cpp
  main.cpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

add_executable(Paddlemonium ${Game_SOURCES})
target_link_libraries(Paddlemonium Forge)
