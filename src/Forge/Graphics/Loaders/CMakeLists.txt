# Graphics - Loaders



set(LoadersSources
	ImageLoader.cpp
	MeshLoader.cpp
	${CMAKE_SOURCE_DIR}/deps_w32/freeimage/FreeImage.lib)

add_library(Loaders ${LoadersSources})

# Link to the shared FreeImage library
if(WIN32)
	add_library(FreeImageDLL SHARED IMPORTED)
	set_property(TARGET FreeImageDLL PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps_w32/freeimage/FreeImage.dll)
	set_property(TARGET FreeImageDLL PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/deps_w32/freeimage/FreeImage.lib)
	target_link_libraries(Loaders FreeImageDLL)
endif()
