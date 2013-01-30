set(UtilSources
	HashUtils.cpp
	Log.cpp
	JsonParser.cpp)

add_library(Util ${UtilSources})
target_link_libraries(Util  ${QT_LIBRARIES})
