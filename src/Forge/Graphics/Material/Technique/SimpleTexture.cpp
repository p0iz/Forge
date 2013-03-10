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

#include "Graphics/Camera.h"
#include "Graphics/Loaders/ImageLoader.h"
#include "Graphics/Light/Light.hpp"
#include "Graphics/RenderTask.h"
#include "Util/JsonParser.h"
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
	// Lighting
	lightsUniformIndex = glGetUniformBlockIndex(shaderProgram.getId(), "Lights");
	glUniformBlockBinding(shaderProgram.getId(), lightsUniformIndex, 1);
	glGenBuffers(1, &lightBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Light) * Light::MAX_LIGHTS, nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Get uniform locations
	wvpLocation = shaderProgram.getUniformLocation("WorldViewProjectionMatrix");
	wvLocation = shaderProgram.getUniformLocation("WorldViewMatrix");
	nLocation = shaderProgram.getUniformLocation("NormalMatrix");

	materialAmbientLoc = shaderProgram.getUniformLocation("materialAmbient");
	materialDiffuseLoc = shaderProgram.getUniformLocation("materialDiffuse");
	materialSpecularLoc = shaderProgram.getUniformLocation("materialSpecular");
	materialShininessLoc = shaderProgram.getUniformLocation("materialShininess");
}

void SimpleTexture::destroy()
{
	freeTextures();
}

void SimpleTexture::freeTextures()
{
	glDeleteTextures(mLoadedTextures.size(), &mLoadedTextures[0]);
}

void SimpleTexture::updateLights(const Light lights[Light::MAX_LIGHTS])
{
	glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Light) * Light::MAX_LIGHTS, lights);
}

void SimpleTexture::updateProperties(const JsonObject& properties)
{
	shaderProgram.use();

	// Diffuse map
	if (properties.hasValue("DiffuseMap")) {
		unsigned int loadedTexture =
			ImageLoader::loadAsTexture(properties.key_values.at("DiffuseMap").value[0].c_str());
		if (loadedTexture > 0) {
			mDiffuseMap = loadedTexture;
			mLoadedTextures.push_back(loadedTexture);
		}
	}

	// Specular map
	if (properties.hasValue("SpecularMap")) {
		unsigned int loadedTexture =
			ImageLoader::loadAsTexture(properties.key_values.at("SpecularMap").value[0].c_str());
		if (loadedTexture > 0) {
			mSpecularMap = loadedTexture;
			mLoadedTextures.push_back(loadedTexture);
		}
	}

	// Normal map
	if (properties.hasValue("NormalMap")) {
		unsigned int loadedTexture =
			ImageLoader::loadAsTexture(properties.key_values.at("NormalMap").value[0].c_str());
		if (loadedTexture > 0) {
			mNormalMap = loadedTexture;
			mLoadedTextures.push_back(loadedTexture);
		}
	}

	// Ambient color reflectivity
	if (properties.hasValue("AmbientColor"))
	{
		float ambientColor[3];
		const std::vector<std::string>& ambientValues = properties.key_values.at("AmbientColor").value;
		ambientColor[0] = ::atof(ambientValues[0].c_str());
		ambientColor[1] = ::atof(ambientValues[1].c_str());
		ambientColor[2] = ::atof(ambientValues[2].c_str());
		glUniform3fv(materialAmbientLoc, 1, ambientColor);
	}

	// Diffuse color reflectivity
	if (properties.hasValue("DiffuseColor"))
	{
		float diffuseColor[3];
		const std::vector<std::string>& diffuseValues = properties.key_values.at("DiffuseColor").value;
		diffuseColor[0] = ::atof(diffuseValues[0].c_str());
		diffuseColor[1] = ::atof(diffuseValues[1].c_str());
		diffuseColor[2] = ::atof(diffuseValues[2].c_str());
		glUniform3fv(materialDiffuseLoc, 1, diffuseColor);
	}

	// Specular color reflectivity
	if (properties.hasValue("SpecularColor"))
	{
		float specularColor[3];
		const std::vector<std::string>& specularValues = properties.key_values.at("SpecularColor").value;
		specularColor[0] = ::atof(specularValues[0].c_str());
		specularColor[1] = ::atof(specularValues[1].c_str());
		specularColor[2] = ::atof(specularValues[2].c_str());
		glUniform3fv(materialSpecularLoc, 1, specularColor);
	}

	// Shininess
	if (properties.hasValue("Shininess"))
	{
		float shininess = ::atof(properties.key_values.at("Shininess").value[0].c_str());
		glUniform1f(materialShininessLoc, shininess);
	}
}

void SimpleTexture::beginMaterial(const RenderTask& task)
{
	shaderProgram.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mDiffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mSpecularMap);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mNormalMap);
	updateLights(task.lights);
}

void SimpleTexture::beginMesh(const RenderTask& task)
{
	// Update
	const Camera& camera = task.getCamera();
	const glm::mat4x4& worldViewTransform = camera.getViewMatrix() * task.getWorldTransform();
	const glm::mat3x3 normalMatrix(worldViewTransform);
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &(camera.getProjectionMatrix() * worldViewTransform)[0][0]);
	glUniformMatrix4fv(wvLocation, 1, GL_FALSE, &worldViewTransform[0][0]);
	glUniformMatrix3fv(nLocation, 1, GL_FALSE, &normalMatrix[0][0]);
}

}
