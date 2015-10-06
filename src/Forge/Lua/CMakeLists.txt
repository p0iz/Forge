# Lua API

include(GenerateExportHeader)

set(ForgeLuaSources
  AssetsLibrary.cpp
  EventLibrary.cpp
  RendererLibrary.cpp
  SceneLibrary.cpp
  LuaState.cpp
  Material.cpp
  Mesh.cpp
  SystemInfo.cpp
)

set(ForgeLuaHeaders
  AssetsLibrary.hpp
  EventLibrary.hpp
  RendererLibrary.hpp
  SceneLibrary.hpp
  Loader.hpp
  LuaForwardDeclarations.hpp
  LuaLibrary.hpp
  LuaState.hpp
  Material.hpp
  Mesh.hpp
  ObjectCreator.hpp
  SystemInfo.hpp
  UserdataMap.hpp
  Utils.hpp
)

add_library(ForgeLua SHARED ${ForgeLuaSources} ${ForgeLuaHeaders})
generate_export_header(ForgeLua
  EXPORT_MACRO_NAME FORGE_EXPORT
  EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/ForgeExport.h
)
add_definitions(-DForgeLua_EXPORTS)
target_link_libraries(ForgeLua PlatformFileSystem PlatformDynamicLoader PlatformEvent PlatformInput PlatformWindow Graphics Util ${ForgeLibDeps})
install(TARGETS ForgeLua DESTINATION bin)
