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
#include "Graphics/Material/Technique/InternalTechniques.hpp"
#include "Graphics/Material/Technique/TechniqueLibrary.h"
#include "Graphics/Scene/SceneLoader.hpp"
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

InGame::~InGame()
{
}

Forge::GameStatePtr InGame::frameUpdate(float const delta) {
  static Forge::GameStateLibrary& library = Forge::GameStateLibrary::getSingleton();

  // Render
  mRenderer.render(mSceneConfig);
  return library.get(getName());
}

void InGame::createState() {
  Forge::TechniqueLibrary::getSingleton().add(new Forge::SimpleTexture);
  Forge::TechniqueLibrary::getSingleton().add(new Forge::SimpleColor);

  Forge::Scene::SceneLoader loader;
  if (loader.loadScene("data/scene/TestScene.lua", mSceneConfig))
  {
    Forge::Log::info << "Scene loaded succesfully\n";
  }

  // Create game view

  // Paddle
  mPaddleNode = mSceneConfig.createSceneNode("PaddleNode");
  mSceneConfig.getSceneNode(mPaddleNode).mWorldTransform.scale(0.2f);

  Forge::MaterialPtr paddleMat =
    Forge::Graphics::MaterialLibrary::getSingleton().getAssetInfo("Paddle").asset;
  Forge::MeshPtr paddleMesh = Forge::Graphics::MeshLibrary::getSingleton().getAssetInfo("paddle").asset;
  paddleMesh->attachToNode(mPaddleNode);

  Forge::MaterialPtr tileMat =
    Forge::Graphics::MaterialLibrary::getSingleton().getAssetInfo("Tile").asset;


  // Tiles
  mTileNode = mSceneConfig.createSceneNode("TileNode");
  mSceneConfig.getSceneNode(mTileNode).mWorldTransform.translate(5.0f, 10.0f, 0.0f).scale(0.2f);

  Forge::MeshPtr tileMesh = Forge::Graphics::MeshLibrary::getSingleton().getAssetInfo("tile").asset;
  tileMesh->attachToNode(mTileNode);

  mTileNode = mSceneConfig.createSceneNode("TileNode2");
  mSceneConfig.getSceneNode(mTileNode).mWorldTransform.translate(6.0f, 10.0f, 0.0f).scale(0.2f);

  tileMesh->attachToNode(mTileNode);


  // Ball
  mBallNode = mSceneConfig.createSceneNode("BallNode");
  mSceneConfig.getSceneNode(mBallNode).mWorldTransform.translate(0.0f, 5.0f, 0.0f).scale(0.2f);

  Forge::MeshPtr ballMesh = Forge::Graphics::MeshLibrary::getSingleton().getAssetInfo("ball").asset;
  ballMesh->attachToNode(mBallNode);


  // Border
  mBorderNode = mSceneConfig.createSceneNode("BorderNode");
  mSceneConfig.getSceneNode(mBorderNode).mWorldTransform.translate(0.0f, 6.1f, 0.0f).rotate(90.0f, glm::vec3(1, 0, 0)).scale(0.4f);

  Forge::MeshPtr borderMesh = Forge::Graphics::MeshLibrary::getSingleton().getAssetInfo("border").asset;
  borderMesh->attachToNode(mBorderNode);


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
