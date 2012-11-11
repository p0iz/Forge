project(Game)

file(GLOB Game_SOURCES *.cpp)
file(GLOB Game_HEADERS *.h)

include_directories(${CMAKE_SOURCE_DIR}/src/Forge)

add_executable(Game ${Game_SOURCES})
target_link_libraries(Game Engine ${QT_LIBRARIES})
