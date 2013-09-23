# Lua API

set(ForgeLuaSources
  State.cpp
)

set(ForgeLuaHeaders
  Loader.hpp
  State.hpp
)

add_library(ForgeLua ${ForgeLuaSources} ${ForgeLuaHeaders})
target_link_libraries(ForgeLua ${LUA_LIBRARIES})
