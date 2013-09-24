# Graphics - Loaders

set(LibrariesSources
  MaterialLibrary.cpp
  MeshLibrary.cpp
  TextureLibrary.cpp
)

set(LibrariesHeaders
  MaterialLibrary.hpp
  MaterialTraits.hpp
  MeshLibrary.hpp
  MeshTraits.hpp
  TextureLibrary.hpp
)

# FreeImage dependency
find_library(FREEIMAGE_LIBRARY NAMES FreeImage freeimage PATHS ${CMAKE_SOURCE_DIR}/windows_deps/freeimage)

add_library(Libraries ${LibrariesSources} ${LibrariesHeaders})

# Link to the shared FreeImage library
if(WIN32)
  add_library(FreeImageDLL SHARED IMPORTED)
  set_property(TARGET FreeImageDLL PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps_w32/freeimage/FreeImage.dll)
  set_property(TARGET FreeImageDLL PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/deps_w32/freeimage/FreeImage.lib)
  list(APPEND LibrariesLibs FreeImageDLL)
else()
  list(APPEND LibrariesLibs ${FREEIMAGE_LIBRARY})
endif()

target_link_libraries(Libraries Graphics ${LibrariesLibs})
