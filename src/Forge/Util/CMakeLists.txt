
set(UtilSources
  Exceptions.cpp
  HashUtils.cpp
  JsonParser.cpp
  Log.cpp
  Singleton.hpp
  UniqueId.hpp
)

add_library(Util ${UtilSources} ${UtilHeaders})
