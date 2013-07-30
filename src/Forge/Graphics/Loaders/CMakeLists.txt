# Graphics - Loaders

set(LoadersSources
  ImageLoader.cpp
  MeshLoader.cpp
)

# FreeImage dependency
find_library(FREEIMAGE_LIBRARY NAMES FreeImage freeimage PATHS ${CMAKE_SOURCE_DIR}/windows_deps/freeimage)

add_library(Loaders ${LoadersSources})

# Link to the shared FreeImage library
if(WIN32)
  add_library(FreeImageDLL SHARED IMPORTED)
  set_property(TARGET FreeImageDLL PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps_w32/freeimage/FreeImage.dll)
  set_property(TARGET FreeImageDLL PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/deps_w32/freeimage/FreeImage.lib)
  list(APPEND LoadersLibs FreeImageDLL)
else()
  list(APPEND LoadersLibs ${FREEIMAGE_LIBRARY})
endif()

target_link_libraries(Loaders Graphics ${LoadersLibs})
