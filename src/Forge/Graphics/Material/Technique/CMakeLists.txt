# Graphics - Material - Technique

set(TechniqueSources
  InternalTechniques.hpp
  DefaultTechnique.cpp
  LuaProperties.cpp
  Property.cpp
  SimpleColor.cpp
  SimpleTexture.cpp
  Technique.h
  TechniqueLibrary.cpp
  UnshadedColor.cpp)

find_package(GLEW REQUIRED)

add_library(Technique ${TechniqueSources})
target_link_libraries(Technique Libraries Shader ${GLEW_LIBRARIES})
