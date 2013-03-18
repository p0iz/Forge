project(Editor)

set(EditorSources
	EditorWindow.ui
	EditorInputHandler.cpp
	EditorWindow.cpp
	main.cpp
	EditorResources.qrc)

find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Gui REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

add_subdirectory(EditorViews)

add_executable(Editor
	${EditorSources})

target_link_libraries(Editor Forge EditorViews)

qt5_use_modules(Editor Gui OpenGL)
qt5_wrap_ui(Editor EditorWindow.ui)
