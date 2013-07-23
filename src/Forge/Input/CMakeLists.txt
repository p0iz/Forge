# Event
set(InputSources
  InputHandler.cpp)

if (USE_QT)
  list(APPEND InputSources
    QtInputHandler.cpp
  )
elseif (WIN32)
  list(APPEND InputSources
    Win32InputHandler.cpp
  )
elseif(APPLE)
elseif(UNIX)
endif()

add_library(Input ${InputSources})
