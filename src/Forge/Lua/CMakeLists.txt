# Lua API

set(ForgeLuaSources
  AssetLoader.cpp
  Material.cpp
  Mesh.cpp
  SceneLoader.cpp
  State.cpp
  Utils.cpp
)

set(ForgeLuaHeaders
  AssetLoader.hpp
  Loader.hpp
  Material.hpp
  Mesh.hpp
  ObjectCreator.hpp
  SceneLoader.hpp
  State.hpp
  Utils.hpp
)

add_library(ForgeLua ${ForgeLuaSources} ${ForgeLuaHeaders})
target_link_libraries(ForgeLua Graphics ${LUA_LIBRARIES})
