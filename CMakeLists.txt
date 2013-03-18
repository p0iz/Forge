cmake_minimum_required(VERSION 2.8.7)

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

# Find and include Qt
find_package(Qt4 REQUIRED COMPONENTS QtOpenGL)
include(${QT_USE_FILE})
include_directories(${QT_INCLUDES})

# Set executable output paths
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Add Forge engine to build
add_subdirectory(src/Forge)

# Add Game to build
add_subdirectory(src/Game)

# Add Editor to build
add_subdirectory(src/Editor)

