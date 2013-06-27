# Graphics

# Add OpenGL component to build
add_subdirectory(OpenGL)

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
	Renderer.cpp
	ResizeEvent.cpp
	TargetCamera.cpp)

add_library(Graphics ${GraphicsSources})

target_link_libraries(Graphics ForgeOpenGL Event Light Loaders Scene Material Text)
