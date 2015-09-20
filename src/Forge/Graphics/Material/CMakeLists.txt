# Graphics - Material

# Add Technique component to Material
add_subdirectory(Technique)

set(MaterialSources
  Material.cpp)

add_library(Material ${MaterialSources})
target_link_libraries(Material Technique)
