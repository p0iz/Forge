# This submodule contains all the facilities required to run Forge
# on a specific platform (Linux, Windows, Mac)
set(PlatformEventSources
  EventHandler.cpp
)

add_library(PlatformEvent ${PlatformEventSources})
