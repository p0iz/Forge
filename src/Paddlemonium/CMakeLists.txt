cmake_minimum_required(VERSION 2.8.8)

project(Paddlemonium)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(Game_SOURCES
	PaddleGame.cpp
	Input/InputHandler.cpp
	State/InGame.cpp
	State/Menu.cpp
	main.cpp)
set(Game_HEADERS
	ForgeGame.h
	GameInputHandler.h)

include_directories(${CMAKE_SOURCE_DIR}/src/Forge ${GLM_DIR})

# Setup Qt MOC'ing
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5OpenGL REQUIRED)

add_executable(Paddlemonium ${Game_SOURCES})
target_link_libraries(Paddlemonium Forge)

qt5_use_modules(Paddlemonium OpenGL)
