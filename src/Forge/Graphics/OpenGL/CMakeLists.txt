# Graphics - Light

set(OpenGLSources
    Blending.cpp
    Buffer.cpp
    DepthTest.cpp
    VertexArray.cpp
    PixelStore.cpp
    Shader.cpp
    ShaderProgram.cpp
    Texture.cpp)

add_library(ForgeOpenGL ${OpenGLSources})
target_link_libraries(ForgeOpenGL ${GLEW_LIBRARY})
