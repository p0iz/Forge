# Window submodule
set(PlatformWindowSources
  RenderWindow.cpp)

if (USE_QT)
  set(ImplSources
    QtRenderWindow.cpp
  )
elseif (WIN32)
  set(ImplSources
    Win32RenderWindow.cpp
  )
elseif(APPLE)
elseif(UNIX)
  set(ImplSources
    X11RenderContext.cpp
    X11RenderWindow.cpp
    RenderWindow_X11.cpp
  )
  set(ImplLibs
    X11
    Xxf86vm
  )
endif()

add_library(PlatformWindow ${PlatformWindowSources} ${ImplSources})
target_link_libraries(PlatformWindow Graphics ${ImplLibs})
