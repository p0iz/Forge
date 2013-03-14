# Graphics - Material

# Add Technique component to Material
add_subdirectory(Technique)

set(MaterialSources
	Material.cpp
	MaterialHandler.cpp
	MaterialLoader.hpp)

add_library(Material ${MaterialSources})
target_link_libraries(Material Graphics Technique)
