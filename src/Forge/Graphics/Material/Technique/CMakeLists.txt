# Graphics - Material - Technique

set(TechniqueSources
	DefaultTechnique.cpp
	Property.cpp
	SimpleTexture.cpp
	TechniqueLibrary.cpp)

add_library(Technique ${TechniqueSources})
target_link_libraries(Technique Loaders)
