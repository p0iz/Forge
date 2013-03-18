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

find_package(Qt5OpenGL REQUIRED)

set(GraphicsSources
	Camera.cpp
	DebugAxis.cpp
	Mesh.cpp
	OrbitalCamera.cpp
	QtRendererBackend.cpp
	QtRenderer.hpp
	Renderer.hpp
	RenderTask.cpp
	SceneNode.cpp
	TestData.cpp
	Transformation.cpp)

add_library(Graphics ${GraphicsSources})

qt5_use_modules(Graphics OpenGL)

target_link_libraries(Graphics Light Loaders Shader Material Text)
