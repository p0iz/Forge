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

#include "SimpleTexture.h"

#include "Graphics/Loaders/ImageLoader.h"
#include "Graphics/Light/Light.hpp"
#include "Util/Log.h"

namespace Forge {

SimpleTexture::SimpleTexture()
	: Technique("SimpleTexture")
{
}

Technique* SimpleTexture::clone()
{
	return new SimpleTexture;
}


void SimpleTexture::create()
{
	// Craft the test cube shaders
	vertexShader.create(GL_VERTEX_SHADER);
	vertexShader.loadCode("data/shaders/SimpleTexture.vs");
	vertexShader.compile();
	fragmentShader.create(GL_FRAGMENT_SHADER);
	fragmentShader.loadCode("data/shaders/SimpleTexture.fs");
	fragmentShader.compile();
	shaderProgram.create();
	shaderProgram.setVertexShader(vertexShader.getId());
	shaderProgram.setFragmentShader(fragmentShader.getId());
	if (shaderProgram.link() != GL_TRUE)
	{
		Log::info << shaderProgram.getProgramInfoLog();
	}
	// Setup light uniform buffer binding
	lightsUniformIndex = glGetUniformBlockIndex(shaderProgram.getId(), "Lights");
	glUniformBlockBinding(shaderProgram.getId(), lightsUniformIndex, Light::UNIFORM_BINDING_POINT);

	// Get uniform locations
	wvpLocation = shaderProgram.getUniformLocation("WorldViewProjectionMatrix");
	wvLocation = shaderProgram.getUniformLocation("WorldViewMatrix");
	nLocation = shaderProgram.getUniformLocation("NormalMatrix");

	materialAmbientLoc = shaderProgram.getUniformLocation("MaterialAmbient");
	materialDiffuseLoc = shaderProgram.getUniformLocation("MaterialDiffuse");
	materialSpecularLoc = shaderProgram.getUniformLocation("MaterialSpecular");
	materialShininessLoc = shaderProgram.getUniformLocation("MaterialShininess");

	mDiffuseMapLoc = shaderProgram.getUniformLocation("DiffuseMap");
	mSpecularMapLoc = shaderProgram.getUniformLocation("SpecularMap");
	mNormalMapLoc = shaderProgram.getUniformLocation("NormalMap");
}

void SimpleTexture::destroy()
{
	freeTextures();
}

void SimpleTexture::freeTextures()
{
	glDeleteTextures(mLoadedTextures.size(), &mLoadedTextures[0]);
}

unsigned int SimpleTexture::addTexture(const std::string& textureFile)
{
	unsigned int loadedTexture = ImageLoader::loadAsTexture(textureFile);
	if (loadedTexture > 0) {
		mLoadedTextures.push_back(loadedTexture);
	}
	return loadedTexture;
}

void SimpleTexture::updateProperties(LuaProperties& properties)
{
	shaderProgram.use();

	// Diffuse map
	if (properties.hasProperty("diffuseMap")) {
		mDiffuseMap = addTexture(properties.getString("diffuseMap"));
		glUniform1i(mDiffuseMapLoc, 0);

	}

	// Specular map
	if (properties.hasProperty("specularMap")) {
		mSpecularMap = addTexture(properties.getString("specularMap"));
		glUniform1i(mSpecularMapLoc, 1);
	}

	// Normal map
	if (properties.hasProperty("normalMap")) {
		mNormalMap = addTexture(properties.getString("normalMap"));
		glUniform1i(mNormalMapLoc, 2);
	}

	// Ambient color reflectivity
	if (properties.hasProperty("ambient"))
	{
		glUniform3fv(materialAmbientLoc, 1, &properties.getFloatArray("ambient")[0]);
	}

	// Diffuse color reflectivity
	if (properties.hasProperty("diffuse"))
	{
		glUniform3fv(materialDiffuseLoc, 1, &properties.getFloatArray("diffuse")[0]);
	}

	// Specular color reflectivity
	if (properties.hasProperty("specular"))
	{
		glUniform3fv(materialSpecularLoc, 1, &properties.getFloatArray("specular")[0]);
	}

	// Shininess
	if (properties.hasProperty("shininess"))
	{
		glUniform1f(materialShininessLoc, properties.getFloat("shininess"));
	}
}

void SimpleTexture::beginMaterial()
{
	shaderProgram.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mDiffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mSpecularMap);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mNormalMap);
}

void SimpleTexture::setTransforms(const glm::mat4& world,
								  const glm::mat4& view,
								  const glm::mat4& projection)
{
	// Update
	const glm::mat4x4 wv = view * world;
	const glm::mat3x3 normalMatrix(wv);
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &(projection * wv)[0][0]);
	glUniformMatrix4fv(wvLocation, 1, GL_FALSE, &wv[0][0]);
	glUniformMatrix3fv(nLocation, 1, GL_FALSE, &normalMatrix[0][0]);
}

}
