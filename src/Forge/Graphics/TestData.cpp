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

#include "TestData.h"

#include "Graphics/MeshLoader.h"
#include "Graphics/ImageLoader.h"
#include "Util/Log.h"
#include "Time/HighResClock.h"

#include <cassert>
#include <sstream>

namespace Forge {

TestData::~TestData()
{
	destroy();
}

void TestData::draw(const glm::mat4x4& viewProjectionMatrix, const glm::mat4x4& viewMatrix)
{
	wvpMatrix = viewProjectionMatrix * testCube->getWorldMatrix();
	worldViewMatrix = viewMatrix * testCube->getWorldMatrix();
	testCubeShaderProgram.use();
	glBindTexture(GL_TEXTURE_2D, testCubeTextureId);
	setTestUniforms(viewMatrix);
	testCube->draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	// Draw debugging axes
	DebugAxis::getInstance().draw(wvpMatrix);

	mLightText.draw();
	mViewText.draw();
}

void TestData::create()
{
	// Craft the test cube
	testCubeTextureId = ImageLoader::loadAsTexture("data/textures/wood.png");
	testCubeVertexShader.create(GL_VERTEX_SHADER);
	testCubeVertexShader.loadCode("data/shaders/TestCubeShader.vert");
	testCubeVertexShader.compile();
	testCubeFragmentShader.create(GL_FRAGMENT_SHADER);
	testCubeFragmentShader.loadCode("data/shaders/TestCubeShader.frag");
	testCubeFragmentShader.compile();
	testCubeShaderProgram.create();
	testCubeShaderProgram.setVertexShader(testCubeVertexShader.getId());
	testCubeShaderProgram.setFragmentShader(testCubeFragmentShader.getId());
	if (testCubeShaderProgram.link() != GL_TRUE)
	{
		std::cout << testCubeShaderProgram.getProgramInfoLog() << std::flush;
	}

	// Get uniform locations

	wvpLocation = testCubeShaderProgram.getUniformLocation("WorldViewProjectionMatrix");
	worldViewLocation = testCubeShaderProgram.getUniformLocation("WorldViewMatrix");

	testLightAmbientLoc = testCubeShaderProgram.getUniformLocation("directional.ambient");
	testLightDiffuseLoc = testCubeShaderProgram.getUniformLocation("directional.diffuse");
	testLightSpecularLoc = testCubeShaderProgram.getUniformLocation("directional.specular");
	testLightDirectionLoc = testCubeShaderProgram.getUniformLocation("directional.direction");

	materialAmbientLoc = testCubeShaderProgram.getUniformLocation("materialAmbient");
	materialDiffuseLoc = testCubeShaderProgram.getUniformLocation("materialDiffuse");
	materialSpecularLoc = testCubeShaderProgram.getUniformLocation("materialSpecular");
	materialShininessLoc = testCubeShaderProgram.getUniformLocation("materialShininess");

	testCube = MeshLoader::loadObjModel("data/cube.obj");
	assert(testCube != nullptr);

	// Create the test text
	mLightText.initialize();
	mLightText.setFont("data/fonts/BaroqueScript.ttf");
	mLightText.setFontSize(24);
	mLightText.setPosition(-0.99,0.5);
	mLightText.setColor(0.0f,0.0f,0.0f,1.0f);
	mLightText.setText("Holy shit! This works! A great success!");
	mViewText.initialize();
	mViewText.setFont("data/fonts/BaroqueScript.ttf");
	mViewText.setFontSize(24);
	mViewText.setPosition(-0.99, 0.75);
	mViewText.setColor(1.0f,0.0f,1.0f,0.2f);


	// Add test light
	mTestLight.ambient = glm::vec4(0.0f, 0.5f, 0.5f, 0.2f);
	mTestLight.diffuse = glm::vec4(0.0f, 1.0f, 0.8f, 0.8f);
	mTestLight.specular = glm::vec4(0.9f, 1.0f, 0.9f, 1.0f);
	mTestLight.direction = glm::vec3(-1.0f, 1.0f, 0.2f);
}

void TestData::destroy()
{
	delete testCube;
	testCube = nullptr;
	glDeleteTextures(1, &testCubeTextureId);
}

void TestData::updateText(int w, int h)
{
	mLightText.setScreenAttributes(w, h);
	mViewText.setScreenAttributes(w, h);
}

void TestData::setTestUniforms(const glm::mat4x4& viewMatrix)
{
	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &wvpMatrix[0][0]);
	glUniformMatrix4fv(worldViewLocation, 1, GL_FALSE, &worldViewMatrix[0][0]);
	glUniform4fv(testLightAmbientLoc, 1, &mTestLight.ambient[0]);
	glUniform4fv(testLightDiffuseLoc, 1, &mTestLight.diffuse[0]);
	glUniform4fv(testLightSpecularLoc, 1, &mTestLight.specular[0]);
	glUniform1f(materialShininessLoc, 16.0f);
	glm::vec3 lightDirection = (glm::mat3(viewMatrix) * mTestLight.direction);
	std::stringstream lightString;
	lightString << "Light direction: " << lightDirection[0] << ", " << lightDirection[1] << ", " << lightDirection[2];
	mLightText.setText(lightString.str().c_str());
	std::stringstream viewString;
	viewString << "View direction: " << viewMatrix[3][0] << ", " << viewMatrix[3][1] << ", " << viewMatrix[3][2];
	mViewText.setText(viewString.str().c_str());

	glUniform3fv(testLightDirectionLoc, 1, &lightDirection[0]);
}

} // namespace Forge
