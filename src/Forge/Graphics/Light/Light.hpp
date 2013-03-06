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
 * Copyright 2013 Tommi Martela
 *
 */

#pragma once

#include <glm/glm.hpp>

namespace Forge {

/* Describes a light in the game world */
struct Light {
	Light();

	glm::vec4 position; // leave w component 0 for directional light
	glm::vec4 color; // alpha component describes light intensity
	struct {
		float constant;
		float linear;
		float quadratic;
	} attenuation; // distance attenuation

	// Spotlight
	float exponent; // Set to 0.0 for point light
	glm::vec3 direction; // spot direction.
	float cutoff; // cutoff angle (in degrees when specified, calculated to cosine when used)
	float falloff; // falloff angle (in degrees when specified, calculated to cosine when used)

	// Padding for std140 GLSL layout
	float padding[3];

	static const int MAX_LIGHTS = 8;
};

}
