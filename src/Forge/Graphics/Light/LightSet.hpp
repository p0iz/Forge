/* This file is part of Forge.
 *
 * Forge is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Forge is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with Forge.  If not, see
 * <http://www.gnu.org/licenses/>. 
 * 
 * Copyright 2012 Tommi Martela
 *
 */

#pragma once

#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

#include <vector>

namespace Forge {

// Class for representing a set of lights
class LightSet
{
public:
	void addLight(DirectionalLight light);
	void addLight(PointLight light);
	void addLight(SpotLight light);

	std::vector<DirectionalLight>::const_iterator getDirectionalLights() const;
	std::vector<PointLight>::const_iterator getPointLights() const;
	std::vector<SpotLight>::const_iterator getSpotLights() const;

private:
	std::vector<DirectionalLight> mDirectionalLights;
	std::vector<PointLight> mPointLights;
	std::vector<SpotLight> mSpotLights;
};

}
