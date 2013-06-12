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

# Add Windows build include directories
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message(STATUS "Adding Windows dependency includes...")
	include_directories(
		${CMAKE_SOURCE_DIR}/windows_deps/glew/include
		${CMAKE_SOURCE_DIR}/windows_deps/glm
		${CMAKE_SOURCE_DIR}/windows_deps/freeimage
		${CMAKE_SOURCE_DIR}/windows_deps/assimp/include
		${CMAKE_SOURCE_DIR}/windows_deps/lua/include
	)
endif()

# Find OpenGL
find_package(OpenGL REQUIRED)

# GLEW dependency (Add PATHS for Windows detection)
find_library(GLEW_LIBRARY NAMES GLEW glew glew32 PATHS ${CMAKE_SOURCE_DIR}/windows_deps/glew/lib)

# FreeImage dependency
find_library(FREEIMAGE_LIBRARY NAMES FreeImage freeimage PATHS ${CMAKE_SOURCE_DIR}/windows_deps/freeimage)

# AssImp dependency
find_library(ASSIMP_LIBRARY NAMES AssImp assimp PATHS ${CMAKE_SOURCE_DIR}/windows_deps/assimp/lib/assimp_debug-dll_x64)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add subsystems
add_subdirectory(Config)
add_subdirectory(State)
add_subdirectory(Graphics)
add_subdirectory(Time)
add_subdirectory(Util)
add_subdirectory(Event)

add_library(Forge ForgeVersion.cpp)
target_link_libraries(Forge
	Config
	State
	Graphics
	Time
	Util
	${GLEW_LIBRARY}
	${FREEIMAGE_LIBRARY}
	${ASSIMP_LIBRARY}
	${OPENGL_LIBRARIES})

if(USE_QT)
	message(STATUS "Creating library with Qt5 support")
	add_subdirectory(Qt)
	target_link_libraries(Forge ${FORGE_QT_LIBRARIES})
endif()
