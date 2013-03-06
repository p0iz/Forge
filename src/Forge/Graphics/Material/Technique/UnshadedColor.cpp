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

#include "Graphics/Camera.h"
#include "Graphics/RenderTask.h"
#include "Util/Log.h"

#include <glm/glm.hpp>

namespace Forge {

UnshadedColor::UnshadedColor()
	: Technique("UnshadedColor")
{
}

Technique* UnshadedColor::clone()
{
	return new UnshadedColor;
}


void UnshadedColor::create()
{
	vertexShader.create(GL_VERTEX_SHADER);
	vertexShader.loadCode("data/shaders/UnshadedColor.vs");
	vertexShader.compile();
	fragmentShader.create(GL_FRAGMENT_SHADER);
	fragmentShader.loadCode("data/shaders/UnshadedColor.fs");
	fragmentShader.compile();
	shaderProgram.create();
	shaderProgram.setVertexShader(vertexShader.getId());
	shaderProgram.setFragmentShader(fragmentShader.getId());
	if (shaderProgram.link() != GL_TRUE)
	{
		Log::error << shaderProgram.getProgramInfoLog();
	}

	// Get uniform location
	wvpLocation = shaderProgram.getUniformLocation("WorldViewProjectionMatrix");
	colorLocation = shaderProgram.getUniformLocation("Color");
}

void UnshadedColor::destroy()
{
}

void UnshadedColor::updateProperties(const JsonObject &)
{
}

void UnshadedColor::beginMaterial(const RenderTask& task)
{
	shaderProgram.use();
	if (hasProperty(HashUtils::StringHash("Color"))) {
		glUniform3fv(colorLocation, 1, getProperty(HashUtils::StringHash("Color")));
	}
}

void UnshadedColor::beginMesh(const RenderTask& task)
{
	// Update
	const Camera& camera = task.getCamera();
	const glm::mat4x4& vp = camera.getViewProjectionMatrix();
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &(vp * task.getWorldTransform())[0][0]);
}

}
