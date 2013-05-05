set(QtStateSources
	QtGameState.cpp
	QtStateMachine.cpp)

find_package(Qt5OpenGL REQUIRED)

add_library(QtState ${QtStateSources})

target_link_libraries(QtState State Graphics)

qt5_use_modules(QtState OpenGL)
