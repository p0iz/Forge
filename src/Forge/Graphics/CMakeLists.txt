# Graphics

# Add Shader component to build
add_subdirectory(Shader)

# Add Text component to build
add_subdirectory(Text)

# Add Light component to build
add_subdirectory(Light)

# Add Loaders component to build
add_subdirectory(Loaders)

# Add Material component to build
add_subdirectory(Material)

# Add Scene component to build
add_subdirectory(Scene)

set(GraphicsSources
	Camera.cpp
	DebugAxis.cpp
	Mesh.cpp
	OrbitalCamera.cpp
	Renderer.hpp
	RenderTask.cpp

add_library(Graphics ${GraphicsSources})

target_link_libraries(Graphics Light Loaders Shader Scene Material Text)
