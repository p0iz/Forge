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
  TargetCamera.cpp
  PositionCamera.cpp
  Mesh.cpp
  OrbitalCamera.cpp
  Renderer.cpp
  Viewport.cpp
)


add_library(Graphics ${GraphicsSources})
target_link_libraries(Graphics
  Light
  Shader
  Scene
  Material
  Text
  PlatformFileSystem
  PlatformWindow
  Util
  ${ForgeLibDeps})