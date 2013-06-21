# Graphics - Text

# FreeType deps
find_library(FREETYPE_LIB NAMES freetype freetype2412MT PATHS ${FREETYPE_DIR}/objs/win32/vc2010)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	include_directories(${FREETYPE_DIR}/include)
else()
	include_directories("/usr/include/freetype2")
endif()

set(TextSources
	Text.cpp)

add_library(Text ${TextSources})
target_link_libraries(Text ${FREETYPE_LIB})
