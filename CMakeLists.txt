cmake_minimum_required(VERSION 2.8.8)

project(Forge)

# Add Forge engine to build
add_subdirectory(src/Forge)

# Install test script
install(FILES "test.lua" DESTINATION ${CMAKE_INSTALL_PREFIX})

# Install test data
install(DIRECTORY data DESTINATION ${CMAKE_INSTALL_PREFIX})
