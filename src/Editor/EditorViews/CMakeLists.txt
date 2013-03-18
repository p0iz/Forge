set(EditorViews_SOURCES
	MaterialEditorView.cpp)
set(EditorViews_HEADERS
	MaterialEditorView.hpp)

include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

add_library(EditorViews
	${EditorViews_SOURCES}
	${EditorViews_HEADERS_MOC})

qt5_use_modules(EditorViews OpenGL)

target_link_libraries(EditorViews ${QT_LIBRARIES})
