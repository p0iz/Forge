cmake_minimum_required(VERSION 2.8.8)

project(Forge)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

# Do build type specific configuration
if(CMAKE_BUILD_TYPE MATCHES Release)
  message(STATUS "Generating Release build.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fomit-frame-pointer -O2")
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
  message(STATUS "Generating Debug build.")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
  set(CMAKE_EXECUTABLE_SUFFIX "_dbg")
endif()

include(ForgeDependencies.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add subsystems
add_subdirectory(Asset)
add_subdirectory(Config)
add_subdirectory(State)
add_subdirectory(Graphics)
add_subdirectory(Lua)
add_subdirectory(Time)
add_subdirectory(Util)
add_subdirectory(Event)
add_subdirectory(Platform)

set(Forge_SRC
  ForgeMain.cpp
)

set(Forge_HDR
  ForgeMain.hpp
  ForgeVersion.hpp
)

add_library(Forge SHARED ${Forge_SRC} ${Forge_HDR})
target_link_libraries(Forge
  Asset
  Config
  State
  Graphics
  Time
  Util
  ForgeLua
  PlatformEvent
  PlatformFileSystem
  PlatformInput
  PlatformWindow
)

if(USE_QT)
  message(STATUS "Creating library with Qt5 support")
  add_subdirectory(Qt)
  target_link_libraries(Forge ${FORGE_QT_LIBRARIES})
endif()
