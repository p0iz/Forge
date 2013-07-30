# Input submodule
set(PlatformInputSources
  InputHandler.cpp)

if (USE_QT)
  list(APPEND PlatformInputSources
    QtInputHandler.cpp
  )
elseif (WIN32)
  list(APPEND PlatformInputSources
    Win32InputHandler.cpp
  )
elseif(APPLE)
elseif(UNIX)
  list(APPEND PlatformInputSources
    X11InputHandler.cpp
    InputHandler_X11.cpp
  )
endif()

add_library(PlatformInput ${PlatformInputSources})
