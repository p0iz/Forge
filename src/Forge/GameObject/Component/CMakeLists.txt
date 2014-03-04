# Components for game objects

set(ComponentSources
  Component.cpp
  MeshComponent.cpp
)

set(ComponentHeaders
  Component.hpp
  MeshComponent.hpp
)

add_library(Component ${ComponentSources} ${ComponentHeaders})
