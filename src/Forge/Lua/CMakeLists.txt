# Lua API

set(ForgeLuaSources
  AssetLoader.cpp
  Material.cpp
  Mesh.cpp
  State.cpp
)

set(ForgeLuaHeaders
  AssetLoader.hpp
  Loader.hpp
  Material.hpp
  Mesh.hpp
  ObjectCreator.hpp
  State.hpp
)

add_library(ForgeLua ${ForgeLuaSources} ${ForgeLuaHeaders})
target_link_libraries(ForgeLua Graphics ${LUA_LIBRARIES})
