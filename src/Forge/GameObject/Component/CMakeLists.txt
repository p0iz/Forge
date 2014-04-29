# Components for game objects

set(ComponentSources
  Camera.cpp
  Component.cpp
  MeshInstance.cpp
  Script.cpp
)

set(ComponentHeaders
  Camera.hpp
  Component.hpp
  ComponentTypes.hpp
  MeshInstance.hpp
  Script.hpp
)

add_library(Component ${ComponentSources} ${ComponentHeaders})
