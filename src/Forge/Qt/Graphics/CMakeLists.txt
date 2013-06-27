set(QtGraphicsSources
	QtRenderer.cpp)

find_package(Qt5OpenGL REQUIRED)

add_library(QtGraphics ${QtGraphicsSources})

qt5_use_modules(QtGraphics OpenGL)

