cmake_minimum_required(VERSION 2.8.8)

project(Paddlemonium)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(Game_SOURCES
  Input/InGameProcessor.cpp
  State/InGame.cpp
  State/Menu.cpp
  main.cpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

if(WIN32)
  set(Win32LinkerFlags "-Wl,--subsystem,windows")

  add_library(ForgeDLL SHARED IMPORTED)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/Forge/Forge.dll)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_IMPLIB ${CMAKE_BINARY_DIR}/src/Forge/libForge.dll.a)
else()
  add_library(ForgeDLL SHARED IMPORTED)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/Forge/libForge.so)
endif()

# Find Lua 5.2 includes
if(WIN32)
  if(NOT LUA_DIR)
    message(ERROR "You need to specify LUA_DIR (Lua installation dir, i.e. the dir with the Makefile)")
  endif()
  include_directories(${LUA_DIR}/src)
else()
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/src/Forge")
  find_package(Lua52 REQUIRED)
  include_directories(${LUA_INCLUDE_DIR})
endif()

add_executable(Paddlemonium ${Game_SOURCES})
target_link_libraries(Paddlemonium ForgeDLL ${Win32LinkerFlags})
