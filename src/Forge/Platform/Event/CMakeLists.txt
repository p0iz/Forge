# This submodule contains all the facilities required to run Forge
# on a specific platform (Linux, Windows, Mac)
set(PlatformEventSources
  EventHandler.cpp
)

if (UNIX)
	list(APPEND PlatformEventSources
		EventHandler_X11.cpp
		X11EventHandler.cpp
	)
endif()

add_library(PlatformEvent ${PlatformEventSources})
