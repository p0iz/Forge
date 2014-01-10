# Lua API

set(ForgeLuaSources
  AssetsLibrary.cpp
  AssetLoader.cpp
  LuaState.cpp
  Material.cpp
  Mesh.cpp
  SceneLoader.cpp
  SystemInfo.cpp
)

set(ForgeLuaHeaders
  AssetsLibrary.hpp
  AssetDir.hpp
  AssetLoader.hpp
  Loader.hpp
  LuaForwardDeclarations.hpp
  LuaLibrary.hpp
  LuaState.hpp
  Material.hpp
  Mesh.hpp
  ObjectCreator.hpp
  SceneLoader.hpp
  SystemInfo.hpp
  Utils.hpp
)

add_library(ForgeLua ${ForgeLuaSources} ${ForgeLuaHeaders})
