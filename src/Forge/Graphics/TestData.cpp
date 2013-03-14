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
#include "Material/Technique/SimpleColor.hpp"
#include "Material/Technique/UnshadedColor.hpp"

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
		task.lights[i].position = task.getCamera().getViewMatrix() * mTestLights[i].position;
		task.lights[i].direction = glm::mat3(task.getCamera().getViewMatrix()) * mTestLights[i].direction;
		task.lights[i].cutoff = glm::cos(glm::radians(mTestLights[i].cutoff));
		task.lights[i].falloff = glm::cos(glm::radians(mTestLights[i].falloff));
	}

	// For each material, draw the meshes that use the material
	cubeMaterial.beginMaterial(task);
	for (Transformation transform : cubeTransforms)
	{
		task.setWorldTransform(transform.getWorldMatrix());
		cubeMaterial.beginMesh(task);
		// Draw first cube
		cubeMesh->draw();
		// Draw debugging axes
		DebugAxis::getInstance().draw(
					task.getCamera().getViewProjectionMatrix() * task.getWorldTransform());
	}

	roomMaterial.beginMaterial(task);
	task.setWorldTransform(roomTransform.getWorldMatrix());
	roomMaterial.beginMesh(task);
	roomMesh->draw();

	// Draw light positions
	if (DebugAxis::isDebugVisible()) {
		lampMaterial.beginMaterial(task);
		for (const Light& light : mTestLights) {
			if (light.position.w > 0.0001f) {
				// Draw point lights
				glm::mat4x4 transform =
						glm::scale(
							glm::translate(glm::mat4x4(),glm::vec3(light.position)),
							glm::vec3(0.3f,0.3f,0.3f));
				task.setWorldTransform(transform);
				lampMaterial.setDynamicProperty("Color", Property(&light.color.r, &light.color.a));
				lampMaterial.beginMesh(task);
				lampMesh->draw();
			} else {
				// draw directional lights in some other way
			}
		}
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
	mTechniqueLibrary.add(new SimpleColor);
	mTechniqueLibrary.add(new UnshadedColor);

	cubeMaterial.loadMaterial("data/materials/Crate.lua", mTechniqueLibrary);
	cubeMesh.reset(MeshLoader::loadMesh("data/crate.obj"));

	lampMaterial.loadMaterial("data/materials/Lamp.lua", mTechniqueLibrary);
	lampMesh.reset(MeshLoader::loadMesh("data/lamp.obj"));

	for (int i = 0; i < NUMBER_OF_CUBES; ++i)
	{
		cubeTransforms[i].translate(CIRCLE_WIDTH*glm::sin(glm::radians(360.0-i*36)),CIRCLE_WIDTH*glm::cos(glm::radians(360.0-i*36)),0.0f);
		cubeTransforms[i].rotate(glm::radians(360.0-i*36), glm::vec3(0,1,0));
	}
	roomMesh.reset(MeshLoader::loadMesh("data/room.obj"));
	roomMaterial.loadMaterial("data/materials/Room.lua", mTechniqueLibrary);
	roomTransform.scale(20);

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

	// Spot
	mTestLights[0].position =	glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	mTestLights[0].color =		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	mTestLights[0].exponent =	100.0f;
	mTestLights[0].direction =	glm::vec3(1.0f, -1.0f, 0.0f);
	mTestLights[0].cutoff =		30.0f;
	mTestLights[0].falloff =	25.0f;

	// Point
	mTestLights[1].position =	glm::vec4(-10.0f, 10.0f, 10.0f, 1.0f);
	mTestLights[1].color =		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// Point
	mTestLights[2].position =	glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	mTestLights[2].color =		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

void TestData::destroy()
{
	cubeMesh.reset();
	for (Transformation& transform : cubeTransforms) {
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
