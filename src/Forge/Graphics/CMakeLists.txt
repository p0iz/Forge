# Graphics

# Add Shader component to build
add_subdirectory(Shader)

# Add Text component to build
add_subdirectory(Text)

# Add Libraries component to build
add_subdirectory(Libraries)

# Add Light component to build
add_subdirectory(Light)

# Add Material component to build
add_subdirectory(Material)

# Add Scene component to build
add_subdirectory(Scene)

set(GraphicsSources
  TargetCamera.cpp
  Camera.cpp
  DebugAxis.cpp
  Mesh.cpp
  OrbitalCamera.cpp
  Renderer.cpp
)

set(GraphicsLibs
  Light
  Libraries
  Shader
  Scene
  Material
  Text
)

add_library(Graphics ${GraphicsSources})
target_link_libraries(Graphics ${GraphicsLibs})
