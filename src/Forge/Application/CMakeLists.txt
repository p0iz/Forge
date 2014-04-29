# Forge application

set(ApplicationSource
  Application.cpp
  ForgeCLI.cpp
)

set(ApplicationHeaders
  Application.hpp
  ForgeCLI.hpp
)

add_library(Application ${ApplicationSource} ${ApplicationHeaders})
