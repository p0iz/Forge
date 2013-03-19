set(QtStateSources
	QtInputHandler.cpp)

find_package(Qt5OpenGL REQUIRED)

add_library(QtInput ${QtStateSources})

qt5_use_modules(QtInput OpenGL)

