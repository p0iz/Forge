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
  RenderContext.cpp
  Renderer.cpp
  RenderWindow.cpp
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
  Loaders
  Shader
  Scene
  Material
  Text
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

# Platform specifics
if(WIN32)
  message(FATAL_ERROR "Windows is not a supported platform... yet.")
elseif(APPLE)
  message(FATAL_ERROR "OSX is not a supported platform... yet.")
elseif(UNIX)
  find_package(X11 REQUIRED)
  include_directories(${X11_INCLUDE_DIRECTORIES})
  list(APPEND GraphicsLibs X11 Xxf86vm)
  list(APPEND GraphicsSources
    RenderWindow_X11.cpp
    X11RenderWindow.cpp
    X11RenderContext.cpp)
endif()

add_library(Graphics ${GraphicsSources})
target_link_libraries(Graphics ${GraphicsLibs})
