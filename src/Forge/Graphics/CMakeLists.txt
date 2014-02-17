# Graphics

# Add Shader component to build
add_subdirectory(Shader)

# Add Text component to build
add_subdirectory(Text)

# Add Light component to build
add_subdirectory(Light)

# Add Material component to build
add_subdirectory(Material)

# Add Scene component to build
add_subdirectory(Scene)

set(GraphicsSources
  Camera.cpp
  DebugAxis.cpp
  Mesh.cpp
  Renderer.cpp
  RendererThread.cpp
  Viewport.cpp
)

set(GraphicsLibs
  Light
  Shader
  Scene
  Technique
  Text
)

add_library(Graphics ${GraphicsSources})
target_link_libraries(Graphics ${GraphicsLibs})
