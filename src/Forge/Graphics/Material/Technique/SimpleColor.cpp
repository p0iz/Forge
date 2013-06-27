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

#include "SimpleColor.hpp"
#include "LuaProperties.hpp"

#include "Graphics/Loaders/ImageLoader.h"
#include "Graphics/Light/Light.hpp"
#include "Util/Log.h"

namespace Forge {

SimpleColor::SimpleColor()
	: Technique("SimpleColor")
{
}

Technique* SimpleColor::clone()
{
	return new SimpleColor;
}


void SimpleColor::create()
{
	// Craft the test cube shaders
	vertexShader.create(Shader::Type::VERTEX_SHADER);
	vertexShader.loadCode("data/shaders/SimpleTexture.vs"); // same vertex shader as SimpleTexture
	vertexShader.compile();
	fragmentShader.create(Shader::Type::FRAGMENT_SHADER);
	fragmentShader.loadCode("data/shaders/SimpleColor.fs");
	fragmentShader.compile();
	shaderProgram.create();
	shaderProgram.setVertexShader(vertexShader.getId());
	shaderProgram.setFragmentShader(fragmentShader.getId());
	if (!shaderProgram.link())
	{
		Log::info << shaderProgram.getProgramInfoLog();
	}
	// Setup light uniform buffer binding
	shaderProgram.bindUniform("Lights", Light::UNIFORM_BINDING_POINT);

	// Get uniform locations
	wvpLocation = shaderProgram.getUniformLocation("WorldViewProjectionMatrix");
	wvLocation = shaderProgram.getUniformLocation("WorldViewMatrix");
	nLocation = shaderProgram.getUniformLocation("NormalMatrix");

	materialAmbientLoc = shaderProgram.getUniformLocation("MaterialAmbient");
	materialDiffuseLoc = shaderProgram.getUniformLocation("MaterialDiffuse");
	materialSpecularLoc = shaderProgram.getUniformLocation("MaterialSpecular");
	materialShininessLoc = shaderProgram.getUniformLocation("MaterialShininess");
}

void SimpleColor::destroy()
{
}

void SimpleColor::updateProperties(LuaProperties& properties)
{
	shaderProgram.use();

	// Ambient color reflectivity
	if (properties.hasProperty("ambient"))
	{
		shaderProgram.setUniform(materialAmbientLoc, 1, 3, &properties.getFloatArray("ambient")[0]);
	}

	// Diffuse color reflectivity
	if (properties.hasProperty("diffuse"))
	{
		shaderProgram.setUniform(materialDiffuseLoc, 1, 3, &properties.getFloatArray("diffuse")[0]);
	}

	// Specular color reflectivity
	if (properties.hasProperty("specular"))
	{
		shaderProgram.setUniform(materialSpecularLoc, 1, 3, &properties.getFloatArray("specular")[0]);
	}

	// Shininess
	if (properties.hasProperty("shininess"))
	{
		float shininess = properties.getFloat("shininess");
		shaderProgram.setUniform(materialShininessLoc, 1, 1, &shininess);
	}
}

void SimpleColor::beginMaterial()
{
	shaderProgram.use();
}

void SimpleColor::setTransforms(const glm::mat4& world,
						   const glm::mat4& view,
						   const glm::mat4& projection)
{
	// Update
	const glm::mat4x4 worldViewTransform = view * world;
	const glm::mat3x3 normalMatrix(worldViewTransform);
	shaderProgram.setUniformMatrix4fv(wvpLocation, 1, false, &(projection * worldViewTransform)[0][0]);
	shaderProgram.setUniformMatrix4fv(wvLocation, 1, false, &worldViewTransform[0][0]);
	shaderProgram.setUniformMatrix3fv(nLocation, 1, false, &normalMatrix[0][0]);
}

}
