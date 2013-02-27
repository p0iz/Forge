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

#include "Camera.h"
#include "RenderTask.h"

#include "Material/Technique/SimpleTexture.h"
#include "Material/Technique/DefaultTechnique.h"

#include "Loaders/ImageLoader.h"
#include "Loaders/MeshLoader.h"

#include "Util/Log.h"
#include "Time/HighResClock.h"

#include <algorithm>
#include <cassert>
#include <sstream>

namespace Forge {

void TestData::draw(RenderTask& task)
{
	for (int i=0; i < Light::MAX_LIGHTS ; ++i) {
		task.lights[i] = mTestLights[i];
		task.lights[i].position = task.getCamera().getViewMatrix() * task.lights[i].position;
	}

	// For each material, draw the meshes that use the material
	for (Transformation transform : transforms)
	{
		task.setModelTransform(transform.getWorldMatrix());
		material.beginMesh(task);
		// Draw first cube
		cubeMesh->draw();
		// Draw debugging axes
		DebugAxis::getInstance().draw(task.getCamera().getViewProjectionMatrix() * task.getModelTransform());
	}

	setTestUniforms(task.getCamera().getViewMatrix());

	// Draw GUI
	mLightText.draw();
	mViewText.draw();
}

void TestData::create()
{
	mTechniqueLibrary.add(new DefaultTechnique);
	mTechniqueLibrary.add(new SimpleTexture);

	cubeMaterial.loadMaterial("data/materials/Crate.json", mTechniqueLibrary);
	cubeMesh.reset(MeshLoader::loadMesh("data/crate.obj"));
	for (int i = 0; i < NUMBER_OF_CUBES; ++i)
	{
		transforms[i].translate(CIRCLE_WIDTH*glm::sin(glm::radians(360.0-i*36)),CIRCLE_WIDTH*glm::cos(glm::radians(360.0-i*36)),0.0f);
		transforms[i].rotate(glm::radians(360.0-i*36), glm::vec3(0,1,0));
	}

	// Create the test text
	mLightText.initialize();
	mLightText.setFont("data/fonts/BaroqueScript.ttf");
	mLightText.setFontSize(12);
	mLightText.setPosition(-0.99,0.5);
	mLightText.setColor(0.0f,0.0f,0.0f,1.0f);
	mViewText.initialize();
	mViewText.setFont("data/fonts/BaroqueScript.ttf");
	mViewText.setFontSize(12);
	mViewText.setPosition(-0.99, 0.75);
	mViewText.setColor(1.0f,0.0f,1.0f,0.2f);


	// Add test light
	std::for_each(mTestLights, &mTestLights[Light::MAX_LIGHTS], [](Light& light)
	{
		light.position =				glm::vec4(0.0f);
		light.color =					glm::vec4(0.0f);
		light.attenuation.constant =	0.1f;
		light.attenuation.linear =		0.1f;
		light.attenuation.quadratic =	0.000025f;
	});

	mTestLights[0].position =	glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	mTestLights[0].color =		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	mTestLights[1].position =	glm::vec4(-10.0f, 10.0f, 5.0f, 1.0f);
	mTestLights[1].color =		glm::vec4(0.0f, 0.0f, 1.0f, 0.8f);
	mTestLights[2].position =	glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	mTestLights[2].color =		glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
	mTestLights[3].position =	glm::vec4(10.0f, -10.0f, 5.0f, 1.0f);
	mTestLights[4].color =		glm::vec4(1.0f, 0.0f, 0.0f, 0.8f);
	Light::ambientColor =		glm::vec4(0.1f,0.1f,0.1f,0.8f);
}

void TestData::destroy()
{
	cubeMesh.reset();
	for (Transformation& transform : transforms) {
		transform.reset();
	}
}

void TestData::updateText(int w, int h)
{
	mLightText.setScreenAttributes(w, h);
	mViewText.setScreenAttributes(w, h);
}

// Update per frame
void TestData::setTestUniforms(const glm::mat4x4& viewMatrix)
{
	std::stringstream lightString;
	lightString << "Light 1 color: " << mTestLights[0].color.x << ", " << mTestLights[0].color.y << ", " << mTestLights[0].color.z;
	mLightText.setText(lightString.str().c_str());
	std::stringstream viewString;
	viewString << "Light 2 color: " << mTestLights[1].color.x << ", " << mTestLights[1].color.y << ", " << mTestLights[1].color.z;
	mViewText.setText(viewString.str().c_str());
}

void TestData::reloadTestMaterial()
{
	cubeMaterial.loadMaterial("data/materials/Crate.json", mTechniqueLibrary);
}

} // namespace Forge
