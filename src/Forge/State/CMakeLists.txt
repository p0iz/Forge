
set(StateSources
	EngineState.cpp
	QtEngineState.cpp
	GameStateMachine.cpp
	QtGameStateMachine.cpp)

# Do Qt stuff for Forge headers
set(MOC_HEADERS
	QtGameStateMachine.hpp)
qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

add_library(State ${StateSources} ${MOC_SOURCES})
target_link_libraries(State ${QT_LIBRARIES})
