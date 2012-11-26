set(EditorViews_SOURCES
	MaterialEditorView.cpp)
set(EditorViews_HEADERS
	MaterialEditorView.hpp)

qt4_wrap_cpp(EditorViews_HEADERS_MOC ${EditorViews_HEADERS})
#qt4_add_resources(Editor_RESOURCE_SOURCES ${Editor_RESOURCES})
# Show us the UI header files!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

add_library(EditorViews
	${EditorViews_SOURCES}
	${EditorViews_HEADERS_MOC})

target_link_libraries(EditorViews ${QT_LIBRARIES})
