# Graphics - Light

set(LightSources
	DirectionalLight.cpp
	LightSet.cpp
	PointLight.cpp
	SpotLight)

add_library(Light ${LightSources})
