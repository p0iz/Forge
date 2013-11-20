# Config

set(ConfigSources
  ConfigLoader.cpp
  Configuration.cpp
)

add_library(Config ${ConfigSources})
target_link_libraries(Config Util ${LUA_LIBRARIES})
