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

#include "Graphics/Camera.h"
#include "Graphics/Loaders/ImageLoader.h"
#include "Graphics/Light/Light.hpp"
#include "Graphics/RenderTask.h"
#include "Util/JsonParser.h"
#include "Util/Log.h"

namespace Forge {

SimpleColor::SimpleColor()
	: Technique("SimpleColor"),
	  mAmbientColorId(HashUtils::StringHash("AmbientColor")),
	  mDiffuseColorId(HashUtils::StringHash("DiffuseColor")),
	  mSpecularColorId(HashUtils::StringHash("SpecularColor")),
	  mShininessId(HashUtils::StringHash("Shininess"))
{
}

Technique* SimpleColor::clone()
{
	return new SimpleColor;
}


void SimpleColor::create()
{
	// Craft the test cube shaders
	vertexShader.create(GL_VERTEX_SHADER);
	vertexShader.loadCode("data/shaders/SimpleTexture.vs"); // same vertex shader as SimpleTexture
	vertexShader.compile();
	fragmentShader.create(GL_FRAGMENT_SHADER);
	fragmentShader.loadCode("data/shaders/SimpleColor.fs");
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

void SimpleColor::destroy()
{
}

void SimpleColor::updateLights(const Light lights[Light::MAX_LIGHTS])
{
	glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Light) * Light::MAX_LIGHTS, lights);
}

void SimpleColor::updateProperties(const JsonObject& properties)
{
	Property property;

	// Ambient color reflectivity
	float ambientColor[3];
	const std::vector<std::string>& ambientValues = properties.key_values.at("AmbientColor").value;
	ambientColor[0] = ::atof(ambientValues[0].c_str());
	ambientColor[1] = ::atof(ambientValues[1].c_str());
	ambientColor[2] = ::atof(ambientValues[2].c_str());
	property.assign(ambientColor, ambientColor+3);
	setProperty(HashUtils::StringHash("AmbientColor"), property);

	property.clear();

	// Diffuse color reflectivity
	float diffuseColor[3];
	const std::vector<std::string>& diffuseValues = properties.key_values.at("DiffuseColor").value;
	diffuseColor[0] = ::atof(diffuseValues[0].c_str());
	diffuseColor[1] = ::atof(diffuseValues[1].c_str());
	diffuseColor[2] = ::atof(diffuseValues[2].c_str());
	property.assign(diffuseColor, diffuseColor+3);
	setProperty(HashUtils::StringHash("DiffuseColor"), property);

	// Specular color reflectivity
	float specularColor[3];
	const std::vector<std::string>& specularValues = properties.key_values.at("SpecularColor").value;
	specularColor[0] = ::atof(specularValues[0].c_str());
	specularColor[1] = ::atof(specularValues[1].c_str());
	specularColor[2] = ::atof(specularValues[2].c_str());
	property.assign(specularColor, specularColor+3);
	setProperty(HashUtils::StringHash("SpecularColor"), property);

	property.clear();

	// Shininess
	property.push_back(::atof(properties.key_values.at("Shininess").value[0].c_str()));
	setProperty(HashUtils::StringHash("Shininess"), property);
}

void SimpleColor::beginMesh(const RenderTask& task)
{
	shaderProgram.use();

	// Update
	const Camera& camera = task.getCamera();
	const glm::mat4x4& worldViewTransform = camera.getViewMatrix() * task.getWorldTransform();
	const glm::mat3x3 normalMatrix(worldViewTransform);
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &(camera.getProjectionMatrix() * worldViewTransform)[0][0]);
	glUniformMatrix4fv(wvLocation, 1, GL_FALSE, &worldViewTransform[0][0]);
	glUniformMatrix3fv(nLocation, 1, GL_FALSE, &normalMatrix[0][0]);
	updateLights(task.lights);

	if (hasProperty(mAmbientColorId))
		glUniform3fv(materialAmbientLoc, 1, getProperty(mAmbientColorId));

	if (hasProperty(mDiffuseColorId))
		glUniform3fv(materialDiffuseLoc, 1, getProperty(mDiffuseColorId));

	if (hasProperty(mSpecularColorId))
		glUniform3fv(materialSpecularLoc, 1, getProperty(mSpecularColorId));

	if (hasProperty(mShininessId))
		glUniform1f(materialShininessLoc, getProperty(mShininessId));
}

}
