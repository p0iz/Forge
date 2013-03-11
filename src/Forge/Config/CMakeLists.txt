# Config

set(ConfigSources
	ConfigHandler.cpp
	ConfigLoader.hpp
	Configuration.hpp)

add_library(Config ${ConfigSources})
target_link_libraries(Config Util)
