# Graphics

# Add Shader component to build
add_subdirectory(Shader)

# Add Text component to build
add_subdirectory(Text)

# Add Light component to build
add_subdirectory(Light)

# Add Material component to build
add_subdirectory(Material)

set(GraphicsSources
  DebugAxis.cpp
  StaticMesh.cpp
  Renderer.cpp
  Viewport.cpp
)

set(GraphicsLibs
  Light
  Shader
  Technique
  Text
)

add_library(Graphics ${GraphicsSources})
target_link_libraries(Graphics ${GraphicsLibs})
