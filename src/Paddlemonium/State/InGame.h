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

// Forge includes
#include "Graphics/Libraries/MeshLibrary.hpp"
#include "Graphics/Libraries/MaterialLibrary.hpp"
#include "Graphics/Light/Light.hpp"
#include "Graphics/Scene/SceneConfig.hpp"
#include "Graphics/Material/Material.h"
#include "Graphics/Renderer.h"
#include "Graphics/TargetCamera.h"
#include "State/GameState.h"
#include "Time/HighResClock.h"

#include <memory>
#include <string>


namespace Paddlemonium { namespace State {

class InGame : public Forge::GameState
{
public:
  InGame(
    Forge::Graphics::Renderer& renderer,
    InGameProcessor& input
  );

  virtual ~InGame();

  virtual Forge::GameStatePtr frameUpdate(float const delta);
  virtual void createState();
  virtual void destroyState();

private:
  InGameProcessor& mInput;

  Forge::TargetCamera mCamera;
  Forge::Graphics::Renderer& mRenderer;

  Forge::SceneConfig mSceneConfig;

  // Game object nodes
  Forge::SceneNodeId mPaddleNode;
  Forge::SceneNodeId mBallNode;
  Forge::SceneNodeId mTileNode;
  Forge::SceneNodeId mBorderNode;
};

}}
