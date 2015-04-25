# Forge application

set(ApplicationSource
  Runner.cpp
)

set(ApplicationHeaders
  Runner.hpp
)

add_library(Application ${ApplicationSource} ${ApplicationHeaders})
