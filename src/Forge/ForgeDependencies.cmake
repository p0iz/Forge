# This file contains all of the dependencies for Forge

# Lua 5.2 dependency
if(WIN32)
  if(NOT LUA_DIR)
  message(ERROR "You need to specify LUA_DIR (Lua 5.2 installation dir)")
  endif()
  include_directories(${LUA_DIR}/include)
  find_library(LUA_LIBRARIES NAMES lua52 PATHS ${LUA_DIR})
else()
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}")
  find_package(Lua52 REQUIRED)
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
  set(FREEIMAGE_LIBRARY ${FreeImageDLL})
  include_directories(${FREEIMAGE_DIR})
else()
  find_library(FREEIMAGE_LIBRARY NAMES FreeImage)
endif()

# OpenGL dependency
find_package(OpenGL REQUIRED)

# GLEW dependency
if(WIN32)
  if(NOT GLEW_DIR)
  message(ERROR "You need to specify GLEW_DIR (GLEW installation dir)")
  endif()
  set(GLEW_INCLUDE_DIRECTORIES "${GLEW_DIR}/include")
  find_library(GLEW_LIBRARIES NAMES glew32 PATHS "${GLEW_DIR}/lib/Release/Win32")
  include_directories(${GLEW_INCLUDE_DIRECTORIES})
else()
  find_package(GLEW REQUIRED)
endif()

#GLM dependency
if(WIN32)
  if(NOT GLM_DIR)
  message(ERROR "You need to specify GLM_DIR (GLM installation dir)")
  endif()
  include_directories(${GLM_DIR})
endif()

# SDL2 dependency
if(UNIX)
  include(FindPkgConfig)
  pkg_search_module(SDL2 REQUIRED sdl2)
elseif(WIN32)
  if(NOT SDL2_DIR)
  message(ERROR "You need to specify SDL2_DIR (SDL2 installation dir)")
  endif()
  if(CMAKE_SIZEOF_VOID EQUAL 8)
  set(SDL2_DIR "${SDL2_DIR}/x86_64-w64-mingw32")
  else()
  set(SDL2_DIR "${SDL2_DIR}/i686-w64-mingw32")
  endif()
  set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
  find_library(SDL2_LIBRARIES NAMES SDL2 PATHS "${SDL2_DIR}/lib")
endif()
include_directories(${SDL2_INCLUDE_DIRS})

# Collect all dependencies in one nice place
set(ForgeLibDeps
  ${SDL2_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${FREEIMAGE_LIBRARY}
  ${FT2_LIB}
  ${LUA_LIBRARIES}
)
