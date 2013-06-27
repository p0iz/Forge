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

#include "Graphics/OpenGL/Buffer.hpp"

#include "Graphics/Scene/Attachable.hpp"

#include <glm/glm.hpp>

namespace Forge {

/* Describes a light in the game world */
struct Light {
	Light();

	enum LightType {
		DIRECTIONAL,
		POINT,
		SPOT,
		DISABLED
	};

	LightType type;
	int id;
	glm::vec4 position;
	glm::vec3 direction;

	/* Light data structure */
	struct Data {
		Data() :
			viewSpacePosition(0.0f),
			color(0.0f),
			exponent(0.0f),
			direction(0.0f),
			cutoff(0.0f),
			falloff(0.0f)
		{
			attenuation.constant = 0.1f;
			attenuation.linear = 0.1f;
			attenuation.quadratic = 0.00025f;
		}

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
		mLightUniformBuffer.create(Buffer::Target::UNIFORM_BUFFER);
		mLightUniformBuffer.setData(sizeof(Light::Data), nullptr, Buffer::Usage::DYNAMIC_DRAW);
		mLightUniformBuffer.setBindingPoint(UNIFORM_BINDING_POINT);
		mLightUniformBuffer.release();
	}

	static void destroyBuffer() {
		mLightUniformBuffer.destroy();
	}

	static void updateBuffer(size_t lightIndex) {
		mLightUniformBuffer.setSubData(0, sizeof(Light::Data), &Light::data[lightIndex]);
	}

	static const int UNIFORM_BINDING_POINT = 1;
	static const int MAX_LIGHTS = 8;
	static Data data[MAX_LIGHTS];
private:
	static Buffer mLightUniformBuffer;
};

}
