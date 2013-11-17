cmake_minimum_required(VERSION 2.8.11)

project(MaterialEditor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(MaterialEditor_SRC
  Connection.cpp
  EditorWindow.cpp
  MaterialNode.cpp
  Node.cpp
  NodeView.cpp
  PropertiesDialog.cpp
  SelectNameDialog.cpp
  TechniqueNode.cpp
  main.cpp
)

set(MaterialEditor_HDR
  Connection.hpp
  EditorWindow.hpp
  MaterialNode.hpp
  Node.hpp
  NodeView.hpp
  PropertiesDialog.hpp
  SelectNameDialog.cpp
  TechniqueNode.hpp
)

set(MaterialEditor_UI
  EditorWindow.ui
  PropertiesDialog.ui
  SelectNameDialog.ui
)

qt5_wrap_ui(UI_HDR ${MaterialEditor_UI})

add_executable(MaterialEditor ${MaterialEditor_SRC} ${MaterialEditor_HDR} ${UI_HDR})
target_link_libraries(MaterialEditor Qt5::Core Qt5::Widgets Util)

