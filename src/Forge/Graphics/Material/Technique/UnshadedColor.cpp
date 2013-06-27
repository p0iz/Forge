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

#include "UnshadedColor.hpp"

#include "Util/Log.h"

#include <glm/glm.hpp>

namespace Forge {

UnshadedColor::UnshadedColor() : Technique("UnshadedColor") { }

Technique* UnshadedColor::clone() {
	return new UnshadedColor;
}

void UnshadedColor::create() {
	vertexShader.create(Shader::Type::VERTEX_SHADER);
	vertexShader.loadCode("data/shaders/UnshadedColor.vs");
	vertexShader.compile();
	fragmentShader.create(Shader::Type::FRAGMENT_SHADER);
	fragmentShader.loadCode("data/shaders/UnshadedColor.fs");
	fragmentShader.compile();
	shaderProgram.create();
	shaderProgram.setVertexShader(vertexShader.getId());
	shaderProgram.setFragmentShader(fragmentShader.getId());
	if (!shaderProgram.link())
	{
		Log::error << shaderProgram.getProgramInfoLog();
	}

	// Get uniform location
	wvpLocation = shaderProgram.getUniformLocation("WorldViewProjectionMatrix");
	colorLocation = shaderProgram.getUniformLocation("Color");
}

void UnshadedColor::destroy() { }

void UnshadedColor::updateProperties(LuaProperties&) { }

void UnshadedColor::beginMaterial() {
	shaderProgram.use();
}

void UnshadedColor::setTransforms(const glm::mat4& world,
							 const glm::mat4& view,
							 const glm::mat4& projection) {
	const glm::mat4x4 wvp = projection * view * world;
	shaderProgram.setUniformMatrix4fv(wvpLocation, 1, false, &(wvp)[0][0]);
	if (hasDynamicProperty("Color")) {
		const float* data = getDynamicProperty("Color");
		shaderProgram.setUniform(colorLocation, 1, 3, data);
	}
}

}
