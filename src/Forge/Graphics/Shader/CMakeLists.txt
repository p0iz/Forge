# Graphics - Shader

set(ShaderSources
  Shader.cpp
  ShaderProgram.cpp)

add_library(Shader ${ShaderSources})
target_link_libraries(Shader ${GLEW_LIBRARIES})
