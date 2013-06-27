
set(UtilSources
	Exceptions.cpp
	HashUtils.cpp
	JsonParser.cpp
	Log.cpp
	LuaLoader.hpp
	Singleton.hpp
	UniqueId.hpp)

add_library(Util ${UtilSources})
target_link_libraries(Util)
