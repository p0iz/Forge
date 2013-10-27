# Lua API

set(ForgeLuaSources
  AssetLoader.cpp
  Material.cpp
  Mesh.cpp
  SceneLoader.cpp
)

set(ForgeLuaHeaders
  AssetDir.hpp
  AssetLoader.hpp
  Loader.hpp
  Material.hpp
  Mesh.hpp
  ObjectCreator.hpp
  SceneLoader.hpp
  Utils.hpp
)

add_library(ForgeLua ${ForgeLuaSources} ${ForgeLuaHeaders})
target_link_libraries(ForgeLua Graphics ${LUA_LIBRARIES})
