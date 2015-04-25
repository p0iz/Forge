# This file contains all of the dependencies for Forge

set(FORGE_DEPS_DIR ${CMAKE_SOURCE_DIR}/src/Dependencies/prefix CACHE PATH "Directory where built dependencies are installed, i.e. the prefix")

message(STATUS "Searching for dependencies in: ${FORGE_DEPS_DIR}")

# Includes from the deps dir
include_directories(${FORGE_DEPS_DIR}/include)

# OpenGL dependency
find_package(OpenGL REQUIRED)

# LuaJIT
include_directories(${FORGE_DEPS_DIR}/include/luajit-2.0)
find_library(LUA_LIBRARY NAMES luajit-5.1 PATHS ${FORGE_DEPS_DIR}/lib NO_DEFAULT_PATH)

# GLEW dependency
find_library(GLEW_LIBRARY NAMES GLEW PATHS ${FORGE_DEPS_DIR}/lib64 NO_DEFAULT_PATH)
add_definitions(-DGLEW_STATIC)

# SDL2 dependencies
find_library(SDL2_LIBRARY NAMES SDL2 PATHS ${FORGE_DEPS_DIR}/lib NO_DEFAULT_PATH)
find_library(SDL2_ttf_LIBRARY NAMES SDL2_ttf PATHS ${FORGE_DEPS_DIR}/lib NO_DEFAULT_PATH)
find_library(SDL2_image_LIBRARY NAMES SDL2_image PATHS ${FORGE_DEPS_DIR}/lib NO_DEFAULT_PATH)

# Collect all dependencies in one nice place
set(ForgeLibDeps
  ${GLEW_LIBRARY}
  ${SDL2_LIBRARY}
  ${SDL2_ttf_LIBRARY}
  ${SDL2_image_LIBRARY}
  ${OPENGL_LIBRARY}
  ${LUA_LIBRARY}
)
