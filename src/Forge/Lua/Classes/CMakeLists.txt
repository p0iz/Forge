# Lua API

set(LuaClassesSources
  LuaGameObject.cpp
  LuaMesh.cpp
  LuaScript.cpp
  LuaTransform.cpp
  LuaClass.cpp
)

set(LuaClassesHeaders
  LuaGameObject.hpp
  LuaMesh.hpp
  LuaScript.hpp
  LuaTransform.hpp
  LuaClass.hpp
)

add_library(Classes ${LuaClassesSources} ${LuaClassesHeaders})
