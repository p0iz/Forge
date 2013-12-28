cmake_minimum_required(VERSION 2.8.8)

project(Forge)

include(GenerateExportHeader)
include(ForgeDependencies.cmake)

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

# Enable position-independent code if not building for Windows
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_compiler_export_flags()
add_definitions(-DForge_EXPORTS)

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

# Remove the unnecessary prefix from windows DLL
if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# The library
add_library(Forge SHARED
  ${Forge_SRC}
  ${Forge_HDR}
  ${AssetHeaders}
)

target_link_libraries(Forge
  "-Wl,--whole-archive"
  Asset
  Config
  Graphics
  Time
  Util
  PlatformEvent
  PlatformFileSystem
  PlatformInput
  PlatformWindow
  ForgeLua
  State
  "-Wl,--no-whole-archive"
  ${ForgeLibDeps}
)
generate_export_header(Forge
  EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/ForgeExport.h
)


if(USE_QT)
  message(STATUS "Creating library with Qt5 support")
  add_subdirectory(Qt)
  target_link_libraries(Forge ${FORGE_QT_LIBRARIES})
endif()
