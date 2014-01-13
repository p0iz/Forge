# This file contains all of the dependencies for Forge

# This file can be used to simplify dependency management on Windows
if(WIN32 AND EXISTS ${CMAKE_SOURCE_DIR}/ForgeWin32Variables.cmake)
  include(${CMAKE_SOURCE_DIR}/ForgeWin32Variables.cmake NO_POLICY_SCOPE)
  message(STATUS "Found a Forge dependency variable file.")
endif()

# Lua 5.2 dependency
if(WIN32)
  if(NOT LUA_DIR)
    message(ERROR "You need to specify LUA_DIR (Lua installation dir, i.e. the dir with the Makefile)")
  endif()
  include_directories(${LUA_DIR}/src)
  find_library(LUA_LIBRARIES NAMES lua PATHS ${LUA_DIR}/src)
else()
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}")
  find_package(Lua52 REQUIRED)
  include_directories(${LUA_INCLUDE_DIR})
endif()

# FreeType dependency
if(WIN32)
  if(NOT FT2_DIR)
  message(ERROR "You need to specify FT2_DIR (FreeType2 dir)")
  endif()
  include_directories(${FT2_DIR}/include)
  find_library(FT2_LIB NAMES freetype PATHS ${FT2_DIR}/objs)
else()
  include_directories("/usr/include/freetype2")
  find_library(FT2_LIB NAMES freetype)
endif()

# FreeImage dependency
if(WIN32)
  if(NOT FREEIMAGE_DIR)
  message(ERROR "You need to specify FREEIMAGE_DIR (FreeImage installation dir)")
  endif()
  add_library(FreeImageDLL SHARED IMPORTED)
  set_property(TARGET FreeImageDLL PROPERTY IMPORTED_LOCATION ${FREEIMAGE_DIR}/FreeImage.dll)
  set_property(TARGET FreeImageDLL PROPERTY IMPORTED_IMPLIB ${FREEIMAGE_DIR}/FreeImage.lib)
  set(FREEIMAGE_LIBRARY FreeImageDLL)
  include_directories(${FREEIMAGE_DIR})
else()
  find_library(FREEIMAGE_LIBRARY NAMES freeimage FreeImage)
endif()

# OpenGL dependency
find_package(OpenGL REQUIRED)

# GLEW dependency
if(WIN32)
  if(NOT GLEW_DIR)
  message(ERROR "You need to specify GLEW_DIR (GLEW installation dir)")
  endif()
  set(GLEW_INCLUDE_DIR "${GLEW_DIR}/include")
  set(GlewArchDir "Win32")
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Linking against 64-bit GLEW")
    set(GlewArchDir "x64")
  else()
    message(STATUS "Linking against 32-bit GLEW")
  endif()
  find_library(GLEW_LIBRARIES NAMES glew32s PATHS ${GLEW_DIR}/lib/Release/${GlewArchDir})
  add_definitions(-DGLEW_STATIC)
  include_directories(${GLEW_INCLUDE_DIR})
else()
  find_package(GLEW REQUIRED)
endif()

#GLM dependency
if(NOT GLM_DIR)
  if(WIN32)
    message(ERROR "You need to specify GLM_DIR (GLM installation dir)")
  elseif(NOT EXISTS "/usr/include/glm")
    message("GLM installation not found in default prefix. Install GLM or set GLM dir to GLM_DIR CMake variable.")
  endif()
elseif(EXISTS "${GLM_DIR}/glm")
  include_directories(${GLM_DIR})
else()
  message("Invalid GLM installation directory: ${GLM_DIR}")
endif()

# SDL2 dependency
if(UNIX)
  include(FindPkgConfig)
  pkg_search_module(SDL2 REQUIRED sdl2)
elseif(WIN32)
  if(NOT SDL2_DIR)
  message(ERROR "You need to specify SDL2_DIR (SDL2 installation dir)")
  endif()
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Linking against 64-bit SDL2")
    set(SDL2_DIR "${SDL2_DIR}/x86_64-w64-mingw32")
  else()
    message(STATUS "Linking against 32-bit SDL2")
    set(SDL2_DIR "${SDL2_DIR}/i686-w64-mingw32")
  endif()
  set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
  find_library(SDL2_LIBRARIES NAMES SDL2 PATHS "${SDL2_DIR}/lib")
endif()
include_directories(${SDL2_INCLUDE_DIRS})

# Collect all dependencies in one nice place
set(ForgeLibDeps
  ${GLEW_LIBRARIES}
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${FREEIMAGE_LIBRARY}
  ${FT2_LIB}
  ${LUA_LIBRARIES}
)
