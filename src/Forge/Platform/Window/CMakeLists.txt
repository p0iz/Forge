# Window submodule
set(PlatformWindowSources
  RenderWindow.cpp
)

add_library(PlatformWindow ${PlatformWindowSources})
target_link_libraries(PlatformWindow Graphics)
