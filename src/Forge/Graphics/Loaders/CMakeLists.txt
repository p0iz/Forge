# Graphics - Loaders

set(LoadersSources
	ImageLoader.cpp
	MeshLoader.cpp)

include_directories(${FREEIMAGE_DIR}/Dist)

add_library(Loaders ${LoadersSources})

target_link_libraries(Loaders ${ASSIMP_LIBRARY})

# Link to the shared FreeImage library
if(WIN32)
    set (FREEIMAGE_PATH "${FREEIMAGE_DIR}\\Dist")
    message(STATUS "Linking against shared FreeImage library in ${FREEIMAGE_PATH}...")
    add_library(FreeImage SHARED IMPORTED)
    set_target_properties(FreeImage PROPERTIES
        IMPORTED_IMPLIB "${FREEIMAGE_PATH}\\FreeImage.lib"
        IMPORTED_LOCATION ${FREEIMAGE_PATH})
    target_link_libraries(Loaders FreeImage)
else()
    # FreeImage dependency
    find_library(FREEIMAGE_LIBRARY NAMES FreeImage freeimage)
    target_link_libraries(Loaders ${FREEIMAGE_LIBRARY})
endif()
