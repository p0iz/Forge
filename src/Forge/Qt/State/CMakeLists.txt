set(QtStateSources
	QtEngineState.cpp
	QtGameStateMachine.cpp)

find_package(Qt5OpenGL REQUIRED)

add_library(QtState ${QtStateSources})

target_link_libraries(QtState State)

qt5_use_modules(QtState OpenGL)
