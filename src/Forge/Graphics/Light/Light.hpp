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

#include "Graphics/Scene/Attachable.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Forge {

/* Describes a light in the game world */
struct Light {
	Light();

	enum LightType {
		DIRECTIONAL,
		POINT,
		SPOT
	};

	LightType type;
	int id;
	glm::vec4 position;

	/* Light data structure */
	struct Data {
		Data() :
			viewSpacePosition(0.0f),
			color(0.0f),
			attenuation({ 0.1f, 0.1f, 0.00025f }),
			exponent(0.0f),
			direction(0.0f),
			cutoff(0.0f),
			falloff(0.0f) { }

		glm::vec4 viewSpacePosition;
		glm::vec4 color; // alpha component describes light intensity
		struct {
			float constant;
			float linear;
			float quadratic;
		} attenuation; // distance attenuation

		// Spotlight
		float exponent;
		glm::vec3 direction; // spot direction.
		float cutoff; // cutoff angle (in degrees when specified, calculated to cosine when used)
		float falloff; // falloff angle (in degrees when specified, calculated to cosine when used)

		// Padding for std140 GLSL layout
		float padding[3];
	};

	static void createBuffer() {
		glGenBuffers(1, &mLightUniformBuffer);
		glBindBuffer(GL_UNIFORM_BUFFER, mLightUniformBuffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(Light::data), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	static void destroyBuffer() {
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glDeleteBuffers(1, &mLightUniformBuffer);
	}

	static void updateBuffer()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, mLightUniformBuffer);
		glBindBufferBase(GL_UNIFORM_BUFFER, UNIFORM_BINDING_POINT, mLightUniformBuffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Light::data), Light::data);
	}

	static const int UNIFORM_BINDING_POINT = 1;
	static const int MAX_LIGHTS = 8;
	static Data data[MAX_LIGHTS];
private:
	static unsigned int mLightUniformBuffer;
};

}
