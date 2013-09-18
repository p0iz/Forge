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
  Camera.cpp
  DebugAxis.cpp
  Mesh.cpp
  OrbitalCamera.cpp
  Renderer.cpp
  ResizeEvent.cpp
  TargetCamera.cpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# GLEW dependency
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRECTORIES})

set(GraphicsLibs
  Event
  Light
  Libraries
  Shader
  Scene
  Material
  Text
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

add_library(Graphics ${GraphicsSources})
target_link_libraries(Graphics ${GraphicsLibs})
