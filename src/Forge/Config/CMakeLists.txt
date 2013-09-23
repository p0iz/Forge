# Config

set(ConfigSources
  ConfigLoader.cpp
  Configuration.cpp)

include_directories(${LUA_INCLUDE_DIRECTORIES})

add_library(Config ${ConfigSources})
target_link_libraries(Config Util)
