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
	if(NOT DEFINED GLEW_DIR)
		message(FATAL_ERROR "You need to define GLEW_DIR as the directory where GLEW is located")
	endif()
	if(NOT DEFINED GLM_DIR)
		message(FATAL_ERROR "You need to define GLM_DIR as the directory where GLM is located")
	endif()
	if(NOT DEFINED FREEIMAGE_DIR)
		message(FATAL_ERROR "You need to define FREEIMAGE_DIR as the directory where FreeImage is located")
	endif()
	if(NOT DEFINED FREETYPE_DIR)
		message(FATAL_ERROR "You need to define FREETYPE_DIR as the directory where FreeType is located")
	endif()
	if(NOT DEFINED ASSIMP_DIR)
		message(FATAL_ERROR "You need to define ASSIMP_DIR as the directory where AssImp is located")
	endif()
	if(NOT DEFINED LUA_DIR)
		message(FATAL_ERROR "You need to define LUA_DIR as the directory where Lua is located (e.g. C:\Lua\5.1)")
	endif()
	message(STATUS "Adding Windows dependency includes...")
	include_directories(
		${GLEW_DIR}/include
                ${GLM_DIR}
		${FREEIMAGE_DIR}/Dist
		${ASSIMP_DIR}/include
		${LUA_DIR}/include
	)
	
	set (GLEW_PATH  "${GLEW_DIR}/lib")
	set (FREEIMAGE_PATH "${FREEIMAGE_DIR}/Dist")
	set (ASSIMP_PATH "${ASSIMP_DIR}/lib/x64")
endif()

# GLEW dependency (Add PATHS for Windows detection)
find_library(GLEW_LIBRARY NAMES GLEW glew glew32 PATHS ${GLEW_PATH})

# FreeImage dependency
find_library(FREEIMAGE_LIBRARY NAMES FreeImage freeimage PATHS ${FREEIMAGE_PATH})

# AssImp dependency
find_library(ASSIMP_LIBRARY NAMES AssImp assimp PATHS ${ASSIMP_PATH})

# Find OpenGL
find_package(OpenGL REQUIRED)

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
