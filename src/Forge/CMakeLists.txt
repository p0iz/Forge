project(Forge)

# GLEW dependency (Add PATHS for Windows detection)
find_library(GLEW_LIBRARY NAMES GLEW glew glew32 PATHS ${CMAKE_SOURCE_DIR}/deps_w32/glew/lib)

# FreeImage dependency
find_library(FREEIMAGE_LIBRARY NAMES FreeImage freeimage PATHS ${CMAKE_SOURCE_DIR}/deps_w32/freeimage)

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
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add subsystems
add_subdirectory(State)
add_subdirectory(Graphics)
add_subdirectory(Input)
add_subdirectory(Time)
add_subdirectory(Util)

add_library(Forge Engine.cpp)
target_link_libraries(Forge
	State
	Graphics
	Input
	Time
	Util
	${GLEW_LIBRARY}
	${FREEIMAGE_LIBRARY}
	${OPENGL_LIBRARIES})
