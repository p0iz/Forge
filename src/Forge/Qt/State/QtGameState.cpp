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

#include "State/QtGameState.h"
#include "State/GameStateLibrary.hpp"

#include "Input/QtInputHandler.h"
#include "Graphics/Loaders/MeshLoader.h"
#include "Graphics/Material/Technique/InternalTechniques.hpp"
#include "Graphics/QtRenderer.hpp"
#include "Time/HighResClock.h"
#include "Util/Log.h"

#include <sstream>

namespace Forge
{

QtGameState::QtGameState(const QString& name,
						 Camera& camera,
						 QtRenderer& renderer,
						 QtInputHandler& input,
						 HighResClock& clock,
						 SceneConfig& config)
	: GameState(name.toStdString()),
	  mCamera(camera),
	  mRenderer(renderer),
	  mInput(input),
	  mClock(clock),
	  mSceneConfig(config) { }

GameStatePtr QtGameState::frameUpdate() {
	static GameStateLibrary& library = GameStateLibrary::getSingleton();

	// Update clock
	mClock.updateDeltaTime();
	float delta = mClock.getGameDelta();

	// Process input
	mInput.processInput(delta);

	// Render
	mRenderer.render(mSceneConfig);

	// Return next (this) state
	return library.get(getName());
}

void QtGameState::createState() {
	createTestScene();
}

void QtGameState::destroyState()
{
}

void QtGameState::createTestScene()
{
	//SceneLoader::loadScene("data/scene/TestScene.lua");
	// Create techniques used in the scene
	mTechniqueLibrary.add(new DefaultTechnique);
	mTechniqueLibrary.add(new SimpleTexture);
	mTechniqueLibrary.add(new SimpleColor);
	mTechniqueLibrary.add(new UnshadedColor);

	createSceneGraph();

	// The test room
	mRoomMaterial.loadMaterial("data/materials/Room.lua", mTechniqueLibrary);
	MeshPtr m = MeshLoader::loadMesh("data/room.obj");

	mSceneConfig.mMaterialMeshMap[mRoomMaterial].push_back(m);
	m->attachToNode(mRoomNodeId);

	// Lamp meshes and materials
	mLampMaterial.loadMaterial("data/materials/Lamp.lua", mTechniqueLibrary);
	m = MeshLoader::loadMesh("data/lamp.obj");
	mSceneConfig.mMaterialMeshMap[mLampMaterial].push_back(m);

	// Test cubes
	mCubeMaterial.loadMaterial("data/materials/Crate.lua", mTechniqueLibrary);
	m = MeshLoader::loadMesh("data/crate.obj");
	for (SceneNodeId node : mCubeNodes) {
		m->attachToNode(node);
	}
	m->attachToNode(mPlayerNode);
	mSceneConfig.mMaterialMeshMap[mCubeMaterial].push_back(m);

	// Green spot
	mSceneConfig.lights[0].id = 0;
	mSceneConfig.lights[0].type = Light::SPOT;
	mSceneConfig.lights[0].position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Light::data[0].color =		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	Light::data[0].exponent =	100.0f;
	Light::data[0].direction =	glm::vec3(1.0f, -1.0f, 0.0f);
	Light::data[0].cutoff =		30.0f;
	Light::data[0].falloff =	25.0f;

	// Blue point
	mSceneConfig.lights[1].id = 1;
	mSceneConfig.lights[1].type = Light::POINT;
	mSceneConfig.lights[1].position = glm::vec4(-10.0f, 10.0f, 10.0f, 1.0f);
	Light::data[1].color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// Red point
	mSceneConfig.lights[2].id = 2;
	mSceneConfig.lights[2].type = Light::POINT;
	mSceneConfig.lights[2].position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Light::data[2].color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	mSceneConfig.setCamera(mCamera);

	mSceneConfig.validateSceneGraph();
	mSceneConfig.calculateWorldTransforms();
}

void QtGameState::createSceneGraph()
{
	mRoomNodeId = mSceneConfig.createSceneNode("RoomNode");
	mSceneConfig.getSceneNode(mRoomNodeId).mWorldTransform.scale(20);

	std::stringstream cubeName;
	for (int i = 0; i < CUBE_NODES; ++i) {
		cubeName.str("");
		cubeName << "CubeNode" << i;
		mCubeNodes[i] = mSceneConfig.createSceneNode(cubeName.str());

		SceneNode& node = mSceneConfig.getSceneNode(mCubeNodes[i]);
		node.mParent = (i - 1) < 0 ? 0 : (i - 1);
		enum { CIRCLE_WIDTH = 10 };
		node.mWorldTransform.translate(CIRCLE_WIDTH*glm::sin(glm::radians(360.0-i*36)),CIRCLE_WIDTH*glm::cos(glm::radians(360.0-i*36)),0.0f);
		node.mWorldTransform.rotate(glm::radians(360.0-i*36), glm::vec3(0,1,0));
	}

	mPlayerNode = mSceneConfig.createSceneNode("PlayerNode");
}

} // namespace Forge
