# Game objects and components

add_subdirectory(Component)

set(GameObjectSources
  Attachable.cpp
  GameObject.cpp
  Transformation.cpp
)

add_library(GameObject ${GameObjectSources})
target_link_libraries(GameObject Component)
