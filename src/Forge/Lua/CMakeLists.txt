# Lua API

set(ForgeLuaSources
  AssetsLibrary.cpp
  RendererLibrary.cpp
  SceneLibrary.cpp
  LuaState.cpp
  Material.cpp
  Mesh.cpp
  SystemInfo.cpp
)

set(ForgeLuaHeaders
  AssetsLibrary.hpp
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
target_link_libraries(ForgeLua PlatformFileSystem PlatformDynamicLoader PlatformWindow Graphics Util ${ForgeLibDeps})