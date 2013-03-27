cmake_minimum_required(VERSION 2.8.8)

# Set executable output paths
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add Forge engine to build
add_subdirectory(src/Forge)

# Add Game to build
add_subdirectory(src/Game)

# Add Editor to build
add_subdirectory(src/Editor)
