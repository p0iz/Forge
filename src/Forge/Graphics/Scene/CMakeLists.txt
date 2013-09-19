# Graphics - Scene

set(SceneSources
  Attachable.cpp
  SceneConfig.cpp
  SceneLoader.cpp
  SceneNode.cpp
  Transformation.cpp)

add_library(Scene ${SceneSources})
target_link_libraries(Scene Libraries Light Util)
