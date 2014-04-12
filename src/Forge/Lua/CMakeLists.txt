# Lua API

set(ForgeLuaSources
  AssetsLibrary.cpp
  ComponentsLibrary.cpp
  RendererLibrary.cpp
  SceneLibrary.cpp
  LuaState.cpp
)

set(ForgeLuaHeaders
  AssetsLibrary.hpp
  ComponentsLibrary.hpp
  RendererLibrary.hpp
  SceneLibrary.hpp
  LuaForwardDeclarations.hpp
  LuaLibrary.hpp
  LuaState.hpp
  Utils.hpp
)

add_library(ForgeLua ${ForgeLuaSources} ${ForgeLuaHeaders})
