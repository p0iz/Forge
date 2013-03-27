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

# GLEW dependency (Add PATHS for Windows detection)
find_library(GLEW_LIBRARY NAMES GLEW glew glew32 PATHS ${CMAKE_SOURCE_DIR}/deps_w32/glew/lib)

# FreeImage dependency
find_library(FREEIMAGE_LIBRARY NAMES FreeImage freeimage PATHS ${CMAKE_SOURCE_DIR}/deps_w32/freeimage)

# AssImp dependency
find_library(ASSIMP_LIBRARY NAMES AssImp assimp PATHS ${CMAKE_SOURCE_DIR}/deps_w32/assimp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Copy GLEW dll
	add_custom_command(TARGET Forge
		COMMAND cmake
		ARGS -E copy_if_different
		${CMAKE_SOURCE_DIR}/deps_w32/glew/lib/glew32.dll
		${CMAKE_BINARY_DIR})
	# Add FreeImage include
	include_directories(${CMAKE_SOURCE_DIR}/deps_w32/freeimage)
	# Copy FreeImage dll
	add_custom_command(TARGET Forge
		COMMAND cmake
		ARGS -E copy_if_different
		${CMAKE_SOURCE_DIR}/deps_w32/freeimage/FreeImage.dll
		${CMAKE_BINARY_DIR})
	# Add AssImp include
	include_directories(${CMAKE_SOURCE_DIR}/deps_w32/assimp/include)
	# Copy AssImp dll
	add_custom_command(TARGET Forge
		COMMAND cmake
		ARGS -E copy_if_different
		${CMAKE_SOURCE_DIR}/deps_w32/assimp/AssImp.dll
		${CMAKE_BINARY_DIR})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add subsystems
add_subdirectory(Config)
add_subdirectory(State)
add_subdirectory(Graphics)
add_subdirectory(Input)
add_subdirectory(Time)
add_subdirectory(Util)

add_library(Forge ForgeConfig.cpp)
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
