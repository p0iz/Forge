cmake_minimum_required(VERSION 2.8.8)

project(Editor)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

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

# Add Windows build include directories
if(WIN32)
  message(STATUS "Adding Windows dependency includes...")
  include_directories(
    ${CMAKE_SOURCE_DIR}/windows_deps/lua/include
  )
else()
  message(STATUS "Including /usr/include/lua5.2")
  include_directories("/usr/include/lua5.2")
endif()

include_directories(${CMAKE_SOURCE_DIR}/src/Forge ${CMAKE_SOURCE_DIR}/src/Forge/Qt)

add_subdirectory(EditorViews)

add_executable(Editor
	${EditorSources})

target_link_libraries(Editor Forge EditorViews)

qt5_use_modules(Editor Gui OpenGL)
qt5_wrap_ui(Editor EditorWindow.ui)
