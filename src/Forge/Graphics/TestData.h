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

#ifndef TESTDATA_H
#define TESTDATA_H

#include "Mesh.h"
#include "Shader/Shader.h"
#include "Light/DirectionalLight.hpp"
#include "Text/Text.hpp"

namespace Forge {

class TestData
{
public:
	~TestData();

	void draw(const glm::mat4x4& viewProjectionMatrix, const glm::mat4x4& viewMatrix);
	void create();
	void destroy();

	void updateText(int w, int h);

	void rotate(float angle, const glm::vec3& axis)
	{
		if (testCube)
			testCube->rotate(angle, axis);
	}

	void translate(float x, float y, float z)
	{
		if (testCube)
			testCube->translate(x, y, z);
	}

	void scale(float x, float y, float z)
	{
		if (testCube)
			testCube->scale(x, y, z);
	}

	operator bool()
	{
		return testCube;
	}

	const bool isCreated() const
	{
		return testCube;
	}

private:
	void setTestUniforms(const glm::mat4x4& viewMatrix);

	// Test data
	Shader testCubeVertexShader;
	Shader testCubeFragmentShader;
	ShaderProgram testCubeShaderProgram;

	unsigned int testCubeTextureId;

	Mesh* testCube;

	Text mLightText;
	Text mViewText;

	// Uniform locations

	unsigned int wvpLocation;
	unsigned int worldViewLocation;

	unsigned int testLightAmbientLoc;
	unsigned int testLightDiffuseLoc;
	unsigned int testLightSpecularLoc;
	unsigned int testLightDirectionLoc;

	unsigned int materialAmbientLoc;
	unsigned int materialDiffuseLoc;
	unsigned int materialSpecularLoc;
	unsigned int materialShininessLoc;

	DirectionalLight mTestLight;

	glm::mat4x4 wvpMatrix;
	glm::mat4x4 worldViewMatrix;
};

} // namespace Forge

#endif // TESTDATA_H
