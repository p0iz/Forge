# Config

set(ConfigSources
	ConfigHandler.cpp
	ConfigLoader.hpp
	Configuration.cpp)

include_directories(${LUA_INCLUDE_DIRECTORIES})

add_library(Config ${ConfigSources})
target_link_libraries(Config Util)
