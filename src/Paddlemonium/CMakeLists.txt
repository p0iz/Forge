cmake_minimum_required(VERSION 2.8.8)

project(Paddlemonium)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(Game_SOURCES
  PaddleGame.cpp
  Input/InGameProcessor.cpp
	State/InGame.cpp
	State/Menu.cpp
  main.cpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

# Add Windows build include directories
if(WIN32)
  message(STATUS "Adding Windows dependency includes...")
  include_directories(
    ${CMAKE_SOURCE_DIR}/windows_deps/glew/include
    ${CMAKE_SOURCE_DIR}/windows_deps/glm
    ${CMAKE_SOURCE_DIR}/windows_deps/freeimage
    ${CMAKE_SOURCE_DIR}/windows_deps/lua/include
  )
elseif(EXISTS "/usr/include/lua5.2")
  include_directories("/usr/include/lua5.2")
else()
  message(FATAL_ERROR "Could not locate Lua 5.2 include directory.")
endif()

add_executable(Paddlemonium ${Game_SOURCES})

target_link_libraries(Paddlemonium Forge )
