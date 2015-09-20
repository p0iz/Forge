cmake_minimum_required(VERSION 3.0.0)

project(Forge)

include(GenerateExportHeader)

#Handle dependencies here
include(ForgeDependencies.cmake)

# Set compiler warning flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

# Forge is written based on the C++11 standard
set(CMAKE_CXX_STANDARD 11)

# Include paths from the project root dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add subsystems
add_subdirectory(Graphics)
add_subdirectory(Util)
add_subdirectory(Platform)

# Add Lua interface
add_subdirectory(Lua)
generate_export_header(ForgeLua
  EXPORT_MACRO_NAME FORGE_EXPORT
  EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/ForgeExport.h
)
add_definitions(-DForgeLua_EXPORTS)

# Add standard asset plugins
add_subdirectory(AssetPlugins)

# The CLI
set(ForgeCLI_SRC
  main.cpp
  ForgeCLI.cpp
)
set(ForgeCLI_HDR
  ForgeCLI.hpp
)
add_executable(forge-cli ${ForgeCLI_SRC} ${ForgeCLI_HDR})
target_link_libraries(forge-cli ForgeLua)
