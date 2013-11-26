# Graphics - Loaders

set(LibrariesSources
  MaterialLibrary.cpp
  MeshLibrary.cpp
  TextureLibrary.cpp
  TechniqueLibrary.cpp
)

set(LibrariesHeaders
  MaterialLibrary.hpp
  MaterialTraits.hpp
  MeshLibrary.hpp
  MeshTraits.hpp
  TechniqueLibrary.hpp
  TechniqueTraits.hpp
  TextureLibrary.hpp
)

add_library(Libraries ${LibrariesSources} ${LibrariesHeaders})
target_link_libraries(Libraries Technique)
