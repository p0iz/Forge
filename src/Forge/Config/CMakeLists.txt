# Config

set(ConfigSources
	ConfigHandler.cpp
	ConfigLoader.hpp
	Configuration.cpp)

if(WIN32)
  include_directories(${CMAKE_SOURCE_DIR}/windows_deps/lua/include)
elseif(EXISTS "/usr/include/lua5.2")
  include_directories("/usr/include/lua5.2")
else()
  message(FATAL_ERROR "Forge requires Lua 5.2 development libraries.")
endif()

add_library(Config ${ConfigSources})
target_link_libraries(Config Util)
