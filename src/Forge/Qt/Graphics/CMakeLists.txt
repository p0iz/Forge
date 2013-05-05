set(QtStateSources
	QtRenderer.cpp)

find_package(Qt5OpenGL REQUIRED)

add_library(QtGraphics ${QtStateSources})

target_link_libraries(QtGraphics Graphics)

qt5_use_modules(QtGraphics OpenGL)

