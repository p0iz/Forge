# Collect all Forge tools here in subdirectories

# Material editor
add_subdirectory(MaterialEditor)

# Ensure that Forge is built first
add_dependencies(MaterialEditor Forge)
