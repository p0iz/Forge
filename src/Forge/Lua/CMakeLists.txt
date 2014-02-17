# Lua API

set(ForgeLuaSources
  AssetsLibrary.cpp
  RendererLibrary.cpp
  SceneLibrary.cpp
  LuaState.cpp
)

set(ForgeLuaHeaders
  AssetsLibrary.hpp
  RendererLibrary.hpp
  SceneLibrary.hpp
  LuaForwardDeclarations.hpp
  LuaLibrary.hpp
  LuaState.hpp
  UserdataMap.hpp
  Utils.hpp
)

add_library(ForgeLua ${ForgeLuaSources} ${ForgeLuaHeaders})
