# Window submodule
set(PlatformWindowSources
  RenderWindow.cpp
  GraphicsContext.cpp
  SDLGraphicsContext.cpp
)

add_library(PlatformWindow ${PlatformWindowSources})
