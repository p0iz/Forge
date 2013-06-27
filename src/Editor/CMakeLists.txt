cmake_minimum_required(VERSION 2.8.8)

project(Editor)

# Set compiler flags
if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(EditorSources
	EditorWindow.ui
	EditorInputHandler.cpp
	EditorWindow.cpp
	main.cpp
	EditorResources.qrc)

# Setup Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Gui REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/Forge ${GLM_DIR})

add_subdirectory(EditorViews)

add_executable(Editor
	${EditorSources})

target_link_libraries(Editor Forge EditorViews)

qt5_use_modules(Editor Gui OpenGL)
qt5_wrap_ui(Editor EditorWindow.ui)
