cmake_minimum_required(VERSION 2.8.8)

project(Forge)

# Set executable output paths
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add Forge engine to build
add_subdirectory(src/Forge)

# Add Tools to build
add_subdirectory(src/Tools)

# Add Game to build
add_subdirectory(src/Paddlemonium)

