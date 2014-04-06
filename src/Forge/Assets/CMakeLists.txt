# Forge asset standard plugin DLLs

if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
  set(Win32LinkerFlags "-Wl,--subsystem,windows -static -static-libstdc++ -static-libgcc")

  add_library(ForgeDLL SHARED IMPORTED)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/Forge/Forge.dll)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_IMPLIB ${CMAKE_BINARY_DIR}/src/Forge/libForge.dll.a)
else()
  add_library(ForgeDLL SHARED IMPORTED)
  set_property(TARGET ForgeDLL PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/Forge/libForge.so)
endif()

# ObjLoader -- loads .obj meshes
set(ObjLoaderSources
  ObjLoader.cpp
)

set(ObjLoaderHeaders
  ObjLoader.hpp
  LoaderInterface.hpp
)

add_library(ObjLoader SHARED ${ObjLoaderSources} ${ObjLoaderHeaders})
target_link_libraries(ObjLoader ForgeDLL ${Win32LinkerFlags})
add_dependencies(ObjLoader Forge)

#ImageLoader -- loads all types of images
set(ImageLoaderSources
  ImageLoader.cpp
)

set(ImageLoaderHeaders
  ImageLoader.hpp
  LoaderInterface.hpp
)

add_library(ImageLoader SHARED ${ImageLoaderSources} ${ImageLoaderHeaders})
target_link_libraries(ImageLoader ForgeDLL ${FREEIMAGE_LIBRARY} ${Win32LinkerFlags})
add_dependencies(ImageLoader Forge)
