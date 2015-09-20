# Forge asset standard plugin DLLs

# ObjLoader -- loads .obj meshes
set(ObjLoaderSources
  ObjLoader.cpp
)

set(ObjLoaderHeaders
  ObjLoader.hpp
  LoaderInterface.hpp
)

add_library(ObjLoader SHARED ${ObjLoaderSources} ${ObjLoaderHeaders})
target_link_libraries(ObjLoader Graphics)

#ImageLoader -- loads all types of images
set(ImageLoaderSources
  ImageLoader.cpp
)

set(ImageLoaderHeaders
  ImageLoader.hpp
  LoaderInterface.hpp
)

add_library(ImageLoader SHARED ${ImageLoaderSources} ${ImageLoaderHeaders})
target_link_libraries(ImageLoader Graphics)