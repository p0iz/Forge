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

#include "DefaultTechnique.h"

#include "Graphics/Camera.h"
#include "Graphics/Scene/SceneConfig.hpp"
#include "LuaProperties.hpp"
#include "Util/Log.h"

#include <glm/glm.hpp>

namespace Forge {

DefaultTechnique::DefaultTechnique()
	: Technique("DefaultTechnique")
{
}

Technique* DefaultTechnique::clone()
{
	return new DefaultTechnique;
}


void DefaultTechnique::create()
{
	vertexShader.create(GL_VERTEX_SHADER);
	vertexShader.loadCode("data/shaders/DefaultTechnique.vs");
	vertexShader.compile();
	fragmentShader.create(GL_FRAGMENT_SHADER);
	fragmentShader.loadCode("data/shaders/DefaultTechnique.fs");
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
}

void DefaultTechnique::destroy()
{
}

void DefaultTechnique::updateProperties(LuaProperties&)
{
}

void DefaultTechnique::beginMaterial()
{
	shaderProgram.use();
}

void DefaultTechnique::setTransforms(const glm::mat4& world,
								const glm::mat4& view,
								const glm::mat4& projection)
{
	// Update
	const glm::mat4x4 wvp = projection * view * world;
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &(wvp)[0][0]);
}

}
