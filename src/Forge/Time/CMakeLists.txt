if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(TimeSources
		HighResClock.cpp)
else()
	set(TimeSources
		HighResClock.cpp
		Timer.cpp)
endif()

add_library(Time ${TimeSources})
