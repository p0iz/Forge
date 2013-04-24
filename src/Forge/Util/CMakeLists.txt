
set(UtilSources
	Exceptions.cpp
	HashUtils.cpp
	JsonParser.cpp
	Log.cpp
	LuaLoader.hpp
	Singleton.hpp
	UniqueId.hpp)

# Lua dependency (Add PATHS for Windows detection)
find_library(LUA_LIBRARY NAMES lua lua5.1 lua5.2 PATHS ${CMAKE_SOURCE_DIR}/windows_deps/lua/lib)

add_library(Util ${UtilSources})
target_link_libraries(Util ${LUA_LIBRARY})
