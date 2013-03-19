project(Game)

set(Game_SOURCES
	ForgeGame.cpp
	GameInputHandler.cpp
	main.cpp)
set(Game_HEADERS
	ForgeGame.h
	GameInputHandler.h)

include_directories(${CMAKE_SOURCE_DIR}/src/Forge ${CMAKE_SOURCE_DIR}/src/Forge/Qt)

# Setup Qt MOC'ing
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5OpenGL REQUIRED)

add_executable(Game ${Game_SOURCES})

target_link_libraries(Game Forge)

qt5_use_modules(Game OpenGL)
