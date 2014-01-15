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

#include "Graphics/Libraries/MaterialLibrary.hpp"
#include "Graphics/Libraries/MeshLibrary.hpp"
#include "State/GameStateLibrary.hpp"
#include "Lua/SceneLoader.hpp"
#include "Platform/Input/InputHandler.hpp"
#include "Time/HighResClock.h"
#include "Util/Log.h"

#include <sstream>


namespace Paddlemonium { namespace State {

InGame::InGame(Forge::ForgeMain& forge):
  GameState("InGame"),
  mSceneConfig(),
  mInputHandler(forge.input()),
  mInput(forge.clock(), mInputHandler, forge.window(), mSceneConfig),
  mCamera(),
  mRenderer(forge.renderer()),
  mWindow(forge.window())
{
}

InGame::~InGame()
{
  if (mInputHandler.currentProcessor() == &mInput)
  {
    mInputHandler.setProcessor(nullptr);
  }
}

void InGame::enter()
{
  mInputHandler.setProcessor(&mInput);
}

Forge::GameStatePtr InGame::frameUpdate(float const delta)
{
  static Forge::GameStateLibrary& library = Forge::GameStateLibrary::instance();

  // Render
  mRenderer.render(mSceneConfig);
  return library.get(getName());
}

void InGame::createState() {
  // Paddle
  mPaddleNode = mSceneConfig.createSceneNode("PaddleNode");
  mSceneConfig.getSceneNode(mPaddleNode).mWorldTransform.scale(0.2f);

  // Tiles
  mTileNode = mSceneConfig.createSceneNode("TileNode");
  mSceneConfig.getSceneNode(mTileNode).mWorldTransform.translate(5.0f, 10.0f, 0.0f).scale(0.2f);

  mTileNode = mSceneConfig.createSceneNode("TileNode2");
  mSceneConfig.getSceneNode(mTileNode).mWorldTransform.translate(6.0f, 10.0f, 0.0f).scale(0.2f);

  // Ball
  mBallNode = mSceneConfig.createSceneNode("BallNode");
  mSceneConfig.getSceneNode(mBallNode).mWorldTransform.translate(0.0f, 5.0f, 0.0f).scale(0.2f);

  // Border
  mBorderNode = mSceneConfig.createSceneNode("BorderNode");
  mSceneConfig.getSceneNode(mBorderNode).mWorldTransform.translate(0.0f, 6.1f, 0.0f).rotate(90.0f, glm::vec3(1, 0, 0)).scale(0.4f);

  Forge::Lua::SceneLoader loader;
  if (loader.loadScene("data/scene/TestScene.lua", mSceneConfig))
  {
    Forge::Log::info << "Scene loaded succesfully\n";
  }

  mCamera.setPosition(0.0f, 5.0f, -20.0f);
  mCamera.setTarget(0.0f, 5.0f, 0.0f);
  mCamera.setPerspectiveProjection(mWindow.width(), mWindow.height());

  // Done. Allow the scene config to manipulate the scene
  mSceneConfig.setCamera(mCamera);
  mSceneConfig.validateSceneGraph();
  mSceneConfig.calculateWorldTransforms();
}

void InGame::destroyState() {
  // Destroy game view
}

}}
