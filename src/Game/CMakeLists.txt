project(Game)

set(Game_SOURCES
	ForgeGame.cpp
	GameInputHandler.cpp
	main.cpp)
set(Game_HEADERS
	ForgeGame.h
	GameInputHandler.h)

include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

add_executable(Game ${Game_SOURCES})
target_link_libraries(Game Engine ${QT_LIBRARIES})
