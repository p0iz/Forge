cmake_minimum_required(VERSION 2.8.8)

project(Forge)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")
if(CMAKE_BUILD_TYPE MATCHES Release)
	message(STATUS "Generating Release build.")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fomit-frame-pointer -O2")
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
	message(STATUS "Generating Debug build.")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_EXECUTABLE_SUFFIX "_dbg")
endif()

# Fix Windows build
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(QT_QMAKE_EXECUTABLE "C:/Qt/4.8.2/bin/qmake.exe")
	include_directories(
		${CMAKE_SOURCE_DIR}/deps_w32/glew/include
		${CMAKE_SOURCE_DIR}/deps_w32/glm)
endif()

# Find OpenGL
find_package(OpenGL REQUIRED)

# Setup Qt MOC'ing
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set executable output paths
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add Forge engine to build
add_subdirectory(src/Forge)

# Add Game to build
add_subdirectory(src/Game)

# Add Editor to build
add_subdirectory(src/Editor)

