# Do Qt stuff for Forge headers
set(MOC_HEADERS
	RendererWidget.h)
qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

# Add Shader component to build
add_subdirectory(Shader)

# Add Text component to build
add_subdirectory(Text)

# Add Light component to build
add_subdirectory(Light)

set(GraphicsSources
	Camera.cpp
	DebugAxis.cpp
	Material.cpp
	Mesh.cpp
	MeshLoader.cpp
	OrbitalCamera.cpp
	RendererWidget.cpp
	SceneNode.cpp
	TestData.cpp
	ImageLoader.cpp
	${MOC_SOURCES})

add_library(Graphics ${GraphicsSources})
target_link_libraries(Graphics Shader Text ${QT_LIBRARIES})
