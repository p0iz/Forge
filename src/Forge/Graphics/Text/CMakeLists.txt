# Graphics - Text

# FreeType deps
find_library(FREETYPE_LIB NAMES freetype PATHS ${CMAKE_SOURCE_DIR}/windows_deps/freetype/objs)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	include_directories(${CMAKE_SOURCE_DIR}/windows_deps/freetype/include)
else()
	include_directories("/usr/include/freetype2")
endif()

set(TextSources
	Text.cpp)

add_library(Text ${TextSources})
target_link_libraries(Text ${FREETYPE_LIB})
