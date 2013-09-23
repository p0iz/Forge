# Graphics - Material

# Add Technique component to Material
add_subdirectory(Technique)

set(MaterialSources
  Material.cpp
  MaterialLoader.cpp)

add_library(Material ${MaterialSources})
target_link_libraries(Material ForgeLua Graphics Technique)
