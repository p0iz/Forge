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

#pragma once

#include "Input/InGameProcessor.hpp"
#include "ForgeMain.hpp"
#include "Graphics/TargetCamera.h"

#include <memory>
#include <string>


namespace Paddlemonium { namespace State {

class InGame : public Forge::GameState
{
public:
  InGame(Forge::ForgeMain& forge);

  virtual ~InGame();

  virtual void enter();
  virtual Forge::GameStatePtr frameUpdate(float const delta);
  virtual void createState();
  virtual void destroyState();

private:
  Forge::SceneConfig mSceneConfig;
  Forge::Input::InputHandler& mInputHandler;
  InGameProcessor mInput;

  Forge::TargetCamera mCamera;
  Forge::Renderer& mRenderer;
  Forge::RenderWindow& mWindow;

  // Game object nodes
  Forge::SceneNodeId mPaddleNode;
  Forge::SceneNodeId mBallNode;
  Forge::SceneNodeId mTileNode;
  Forge::SceneNodeId mBorderNode;
};

}}
