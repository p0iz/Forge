# Lua API

set(ForgeLuaSources
  InputLibrary.cpp
  RendererLibrary.cpp
  LuaState.cpp
)

set(ForgeLuaHeaders
  InputLibrary.hpp
  RendererLibrary.hpp
  LuaForwardDeclarations.hpp
  LuaLibrary.hpp
  LuaState.hpp
  Utils.hpp
)

add_subdirectory(Classes)

add_library(ForgeLua ${ForgeLuaSources} ${ForgeLuaHeaders})
target_link_libraries(ForgeLua Classes)
