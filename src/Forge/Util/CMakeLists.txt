
set(UtilSources
	HashUtils.cpp
	JsonParser.cpp
	Log.cpp
	LuaLoader.hpp
	Singleton.hpp)

# Lua dependency (Add PATHS for Windows detection)
find_library(LUA_LIBRARY NAMES lua lua5.2 Lua Lua5.2 PATHS ${CMAKE_SOURCE_DIR}/deps_w32/lua/lib)

add_library(Util ${UtilSources})
target_link_libraries(Util ${LUA_LIBRARY} ${QT_LIBRARIES})
