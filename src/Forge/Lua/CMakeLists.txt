# Lua API

set(ForgeLuaSources
  AssetLoader.cpp
  LuaState.cpp
  Material.cpp
  Mesh.cpp
  SceneLoader.cpp
  SystemInfo.cpp
)

set(ForgeLuaHeaders
  AssetDir.hpp
  AssetLoader.hpp
  Loader.hpp
  LuaLibrary.hpp
  LuaScript.hpp
  LuaState.hpp
  Material.hpp
  Mesh.hpp
  ObjectCreator.hpp
  SceneLoader.hpp
  SystemInfo.hpp
  Utils.hpp
)

add_library(ForgeLua ${ForgeLuaSources} ${ForgeLuaHeaders})
