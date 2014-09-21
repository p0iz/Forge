cmake_minimum_required(VERSION 2.8.8)

project(Forge)

include(GenerateExportHeader)

#Handle dependencies here
include(ForgeDependencies.cmake)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -fno-exceptions")

# Add deps prefix
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/deps ${CMAKE_PREFIX_PATH})

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
add_subdirectory(Application)
add_subdirectory(Assets)
add_subdirectory(GameObject)
add_subdirectory(Graphics)
add_subdirectory(Lua)
add_subdirectory(Time)
add_subdirectory(Util)
add_subdirectory(Platform)

# Remove the unnecessary prefix from windows DLL and link statically to GCC and stdlibc++
if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
  set(Win32LinkerFlag "-static -static-libstdc++ -static-libgcc")
endif()

# The library
add_library(Forge SHARED Application)

target_link_libraries(Forge
  "-Wl,--whole-archive"
  Application
  GameObject
  Component
  Graphics
  Time
  Util
  PlatformDynamicLoader
  PlatformEvent
  PlatformFileSystem
  PlatformInput
  PlatformWindow
  ForgeLua
  "-Wl,--no-whole-archive"
  ${ForgeLibDeps}
  ${Win32LinkerFlag}
)
generate_export_header(Forge
  EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/ForgeExport.h
)
