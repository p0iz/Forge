# Graphics - Loaders

set(LoadersSources
	ImageLoader.cpp
	MeshLoader.cpp)

add_library(Loaders ${LoadersSources})

# Link to the shared FreeImage library
if(WIN32)
	add_library(FreeImageDLL SHARED IMPORTED)
        set_property(TARGET FreeImageDLL PROPERTY IMPORTED_LOCATION ${FREEIMAGE_PATH}/FreeImage.dll)
        set_property(TARGET FreeImageDLL PROPERTY IMPORTED_IMPLIB ${FREEIMAGE_PATH}/FreeImage.lib)
	target_link_libraries(Loaders FreeImageDLL)
endif()
