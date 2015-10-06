# This file contains all of the dependencies for Forge

# This file can be used to simplify dependency management on Windows
if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Linking against 64-bit dependencies")
    set(Is64bit TRUE)
  else()
    message(STATUS "Linking against 32-bit dependencies")
	set(Is64bit FALSE)
  endif()
endif()

# LuaJIT dependency
if(WIN32)
  set(LUA_DIR "${CMAKE_SOURCE_DIR}/deps/luajit")
  if(NOT EXISTS "${LUA_DIR}")
    message(ERROR "You need to add a compiled LuaJIT release into 'deps/luajit' (http://luajit.org/download.html)")
  endif()
  include_directories(${LUA_DIR}/src)
  find_library(LUA_LIBRARIES NAMES lua51 PATHS ${LUA_DIR}/src)
  if (LUA_LIBRARIES)
    install(
      DIRECTORY ${LUA_DIR}/src/
      DESTINATION bin
      FILES_MATCHING PATTERN "*.dll"
      PATTERN "host" EXCLUDE
      PATTERN "jit" EXCLUDE)
  endif()
else()
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}")
  find_package(Lua51 REQUIRED)
  include_directories(${LUA_INCLUDE_DIR})
endif()

# OpenGL dependency
find_package(OpenGL REQUIRED)

# GLEW dependency
if(WIN32)
  set(GLEW_DIR "${CMAKE_SOURCE_DIR}/deps/glew")
  if(NOT EXISTS ${GLEW_DIR})
    message(ERROR "You need to add a GLEW release to 'deps/glew' (http://glew.sourceforge.net/)")
  endif()

  set(GlewArchDir "Win32")
  if(Is64bit)
    message(STATUS "Linking against 64-bit GLEW")
    set(GlewArchDir "x64")
  endif()
  find_library(GLEW_LIBRARIES NAMES glew32s PATHS ${GLEW_DIR}/lib/Release/${GlewArchDir})
  add_definitions(-DGLEW_STATIC)
  include_directories(${GLEW_DIR}/include)
else()
  find_package(GLEW REQUIRED)
endif()

#GLM dependency
set(GLM_DIR "${CMAKE_SOURCE_DIR}/ext/glm")
if(NOT EXISTS ${GLM_DIR})
  message(ERROR "You need to initialize and update the GLM Git submodule into 'ext/glm' (https://github.com/g-truc/glm/releases)")
else()
  include_directories(${GLM_DIR})
endif()

# SDL2 dependency
set(SDL2_LIB_PATH_SUFFIX "x86")
if(Is64bit)
  set(SDL2_LIB_PATH_SUFFIX "x64")
endif()

if(UNIX)
  include(FindPkgConfig)
  pkg_search_module(SDL2 REQUIRED sdl2)
  find_library(SDL2_IMAGE_LIB NAMES sdl2_image)
  find_library(SDL2_TTF_LIB NAMES sdl2_ttf)
elseif(WIN32)
  set(SDL2_DIR "${CMAKE_SOURCE_DIR}/deps/sdl2")
  if(NOT EXISTS ${SDL2_DIR})
    message(ERROR "You need to add development binaries for SDL2, SDL2_image and SDL2_ttf into 'deps/sdl2' and then move the includes into a new include/SDL2 folder (https://www.libsdl.org/download-2.0.php)")
  endif()
  set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
  find_library(SDL2_LIBRARIES NAMES SDL2 PATHS "${SDL2_DIR}/lib/${SDL2_LIB_PATH_SUFFIX}")
  find_library(SDL2_IMAGE_LIB NAMES sdl2_image PATHS ${SDL2_DIR}/lib/${SDL2_LIB_PATH_SUFFIX})
  find_library(SDL2_TTF_LIB NAMES sdl2_ttf PATHS ${SDL2_DIR}/lib/${SDL2_LIB_PATH_SUFFIX})
  if (SDL2_LIBRARIES AND SDL2_IMAGE_LIB AND SDL2_TTF_LIB)
    install(
      DIRECTORY ${SDL2_DIR}/lib/${SDL2_LIB_PATH_SUFFIX}/
      DESTINATION bin
      FILES_MATCHING PATTERN "*.dll")
  endif()
endif()
include_directories(${SDL2_INCLUDE_DIRS})

# Collect all dependencies in one nice place
set(ForgeLibDeps
  ${LUA_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIB}
  ${SDL2_TTF_LIB}
)
