set(QtInputSources
	QtInputHandler.cpp)

find_package(Qt5OpenGL REQUIRED)

add_library(QtInput ${QtInputSources})

qt5_use_modules(QtInput OpenGL)

