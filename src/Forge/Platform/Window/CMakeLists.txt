# Window submodule
set(PlatformWindowSources
  SDLGraphicsContext.cpp
  RenderWindow.cpp
)

add_library(PlatformWindow ${PlatformWindowSources})
target_link_libraries(PlatformWindow Util ${ForgeLibDeps})