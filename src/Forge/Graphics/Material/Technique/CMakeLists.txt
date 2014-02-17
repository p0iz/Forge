# Graphics - Material - Technique

set(TechniqueSources
  DefaultTechnique.cpp
  Technique.cpp
)

add_library(Technique ${TechniqueSources})
target_link_libraries(Technique Shader)
