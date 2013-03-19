# A build configuration for Qt-specific classes

# Setup Qt MOC'ing
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include both the Qt-specific and Forge sources in includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../)

# Add relevant subsystems
add_subdirectory(Graphics)
add_subdirectory(Input)
add_subdirectory(State)

# Finally, add the relevant libraries to a variable in the parent scope
set(FORGE_QT_LIBRARIES QtGraphics QtInput QtState PARENT_SCOPE)
