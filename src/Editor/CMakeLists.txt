project(Editor)

file(GLOB Editor_SOURCES *.cpp)
file(GLOB Editor_HEADERS *.h)
file(GLOB Editor_UIS *.ui)
file(GLOB Editor_RESOURCES *.qrc)

qt4_wrap_cpp(Editor_HEADERS_MOC ${Editor_HEADERS})
qt4_wrap_ui(Editor_UI_SOURCES ${Editor_UIS})
qt4_add_resources(Editor_RESOURCE_SOURCES ${Editor_RESOURCES})
# Show us the UI header files!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

add_subdirectory(EditorViews)

add_executable(Editor
	${Editor_SOURCES}
	${Editor_HEADERS_MOC}
	${Editor_UI_SOURCES}
	${Editor_RESOURCE_SOURCES})

target_link_libraries(Editor Engine EditorViews ${QT_LIBRARIES})
