project(Engine)

# GLEW dependency (Add PATHS for Windows detection)
find_library(GLEW_LIBRARY NAMES GLEW glew glew32 PATHS ${CMAKE_SOURCE_DIR}/deps_w32/glew/lib)

# Copy GLEW dll to Windows build
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_custom_command(TARGET Forge
		COMMAND cmake
		ARGS -E copy_if_different
		${CMAKE_SOURCE_DIR}/deps_w32/glew/lib/glew32.dll
		${CMAKE_BINARY_DIR})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add subsystems
add_subdirectory(State)
add_subdirectory(Graphics)
add_subdirectory(Input)
add_subdirectory(Time)
add_subdirectory(Util)

add_library(Engine Engine.cpp)
target_link_libraries(Engine
	State
	Graphics
	Input
	Time
	Util
	${GLEW_LIBRARY}
	${OPENGL_LIBRARIES})
