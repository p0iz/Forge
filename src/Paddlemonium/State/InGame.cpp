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

#include "InGame.h"

#include "State/GameStateLibrary.hpp"
#include "Graphics/Loaders/MeshLoader.h"
#include "Graphics/Material/Technique/InternalTechniques.hpp"
#include "Platform/Input/InputHandler.hpp"
#include "Time/HighResClock.h"
#include "Util/Log.h"

#include <sstream>


namespace Paddlemonium { namespace State {

InGame::InGame(
    Forge::Graphics::Renderer& renderer,
    InGameProcessor& input
  ):
  GameState("InGame"),
  mInput(input),
  mRenderer(renderer)
{
}

Forge::GameStatePtr InGame::frameUpdate(float const delta) {
  static Forge::GameStateLibrary& library = Forge::GameStateLibrary::getSingleton();

  // Render
  mRenderer.render(mSceneConfig);

  // Return next (this) state
  //if (mInput->isKeyDown(' ') {
    // Return paused state
  //}
  return library.get(getName());
}

void InGame::createState() {
  mTechniqueLibrary.add(new Forge::SimpleTexture);
  mTechniqueLibrary.add(new Forge::SimpleColor);

  Forge::Light light;
  light.position = glm::vec4(10.0f, 10.0f, 1.0f, 1.0f);
  light.type = Forge::Light::POINT;
  light.getShaderData().color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  mSceneConfig.lights.push_back(light);

  // Create game view
  mPaddleMesh = Forge::MeshLoader::loadMesh("data/paddle.obj");
  mPaddleNode = mSceneConfig.createSceneNode("PaddleNode");
  mSceneConfig.getSceneNode(mPaddleNode).mWorldTransform.scale(0.2f);
  Forge::Material material;
  material.loadMaterial("data/materials/Paddle.material", mTechniqueLibrary);
  mSceneConfig.mMaterialMeshMap[material].push_back(mPaddleMesh);
  mPaddleMesh->attachToNode(mPaddleNode);

  mTileMesh = Forge::MeshLoader::loadMesh("data/tile.obj");
  material.loadMaterial("data/materials/Tile.material", mTechniqueLibrary);
  mSceneConfig.mMaterialMeshMap[material].push_back(mTileMesh);

  mTileNode = mSceneConfig.createSceneNode("TileNode");
  mTileMesh->attachToNode(mTileNode);
  mSceneConfig.getSceneNode(mTileNode).mWorldTransform.translate(5.0f, 10.0f, 0.0f).scale(0.2f);

  mTileNode = mSceneConfig.createSceneNode("TileNode2");
  mTileMesh->attachToNode(mTileNode);
  mSceneConfig.getSceneNode(mTileNode).mWorldTransform.translate(6.0f, 10.0f, 0.0f).scale(0.2f);

  mBallMesh = Forge::MeshLoader::loadMesh("data/ball.obj");
  mSceneConfig.mMaterialMeshMap[material].push_back(mBallMesh); // Use same material for ball

  mBallNode = mSceneConfig.createSceneNode("BallNode");
  mBallMesh->attachToNode(mBallNode);
  mSceneConfig.getSceneNode(mBallNode).mWorldTransform.translate(0.0f, 5.0f, 0.0f).scale(0.2f);

  mBorderMesh = Forge::MeshLoader::loadMesh("data/border.obj");
  mSceneConfig.mMaterialMeshMap[material].push_back(mBorderMesh); // Use same material for ball

  mBorderNode = mSceneConfig.createSceneNode("BorderNode");
  mBorderMesh->attachToNode(mBorderNode);
  mSceneConfig.getSceneNode(mBorderNode).mWorldTransform.translate(0.0f, 6.1f, 0.0f).rotate(90.0f, glm::vec3(1, 0, 0)).scale(0.4f);



  mCamera.setPosition(0.0f, 5.0f, -20.0f);
  mCamera.setTarget(0.0f, 5.0f, 0.0f);
  mCamera.setPerspectiveProjection(mRenderer.getWidth(), mRenderer.getHeight());

  // Done. Allow the scene config to manipulate the scene
  mSceneConfig.setCamera(mCamera);
  mInput.setSceneConfig(&mSceneConfig);

  mSceneConfig.validateSceneGraph();
  mSceneConfig.calculateWorldTransforms();
}

void InGame::destroyState() {
  // Destroy game view
}

}}
