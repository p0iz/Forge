project(Game)

set(Game_SOURCES
	ForgeGame.cpp
	GameInputHandler.cpp
	main.cpp)
set(Game_HEADERS
	ForgeGame.h
	GameInputHandler.h)

include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

find_package(Qt5OpenGL REQUIRED)

add_executable(Game ${Game_SOURCES})

target_link_libraries(Game Forge ${QT_LIBRARIES})

qt5_use_modules(Game OpenGL)
