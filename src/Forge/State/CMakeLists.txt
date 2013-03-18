
set(StateSources
	EngineState.cpp
	QtEngineState.cpp
	GameStateMachine.cpp
	QtGameStateMachine.cpp)

find_package(Qt5OpenGL REQUIRED)

add_library(State ${StateSources})

qt5_use_modules(State OpenGL)
