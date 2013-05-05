# Graphics - Material - Technique

set(TechniqueSources
	InternalTechniques.hpp
	DefaultTechnique.cpp
	LuaProperties.cpp
	Property.cpp
	SimpleColor.cpp
	SimpleTexture.cpp
	Technique.h
	TechniqueLibrary.cpp
	UnshadedColor.cpp)

add_library(Technique ${TechniqueSources})
target_link_libraries(Technique Loaders)
