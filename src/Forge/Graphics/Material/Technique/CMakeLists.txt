# Graphics - Material - Technique

set(TechniqueSources
  DefaultTechnique.cpp
  Technique.cpp
  TechniqueLoader.cpp)

find_package(GLEW REQUIRED)

add_library(Technique ${TechniqueSources})
target_link_libraries(Technique Libraries Shader ${GLEW_LIBRARIES})
