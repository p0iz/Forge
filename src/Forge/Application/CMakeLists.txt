# Forge application

set(ApplicationSource
  ForgeCLI.cpp
)

set(ApplicationHeaders
  ForgeCLI.hpp
)

add_library(Application ${ApplicationSource} ${ApplicationHeaders})
