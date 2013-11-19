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

#include "InGameProcessor.hpp"
#include "Graphics/DebugAxis.h"
#include "Platform/Input/KeySymbols.hpp"
#include "Util/Log.h"

#include <map>


namespace Paddlemonium {

// TODO: Make a config with this stuff
namespace {
  const int MOVE_SPEED = 10.0f;
}

InGameProcessor::InGameProcessor(
  Forge::HighResClock& clock,
  Forge::Input::InputHandler& input,
  Forge::Graphics::RenderWindow& window,
  Forge::SceneConfig& scene
):
  mScene(scene),
  mKeyMap(),
  mClock(clock),
  mInputHandler(input),
  mWindow(window)
{
  mapDefaultKeys();
}

InGameProcessor::~InGameProcessor()
{
}

bool InGameProcessor::process(const float delta)
{
  processMouseMove();

  return processKeyPress(delta);
}

void InGameProcessor::processMouseMove()
{
  const Forge::Camera& camera = mScene.getCamera();
  Forge::SceneNode& paddleNode = mScene.getSceneNode("PaddleNode");

  float distance = (camera.getViewMatrix() * paddleNode.mWorldTransform.getMatrix())[3][2];
  float frustumHeight = glm::tan(glm::radians(camera.getFovY() * 0.5f)) * distance;
  float frustumWidth = camera.getAspectRatio() * frustumHeight;
  float percentageX = static_cast<float>(mInputHandler.getMouseX()) / mWindow.width();
  float screenPos = frustumWidth * (2 * percentageX - 1);

  paddleNode.mWorldTransform.setPosition(screenPos, 0.0f, 0.0f);
}

bool InGameProcessor::processKeyPress(float const delta)
{
  using Forge::Key;

  for (Key key : mInputHandler.getPressedKeys())
  {
    switch (mKeyMap[key])
    {
      case PaddleLeft:
      {
        Forge::SceneNode& paddleNode = mScene.getSceneNode("PaddleNode");
        paddleNode.mWorldTransform.translate(-10 * delta, 0, 0);
        break;
      }
      case PaddleRight:
      {
        Forge::SceneNode& paddleNode = mScene.getSceneNode("PaddleNode");
        paddleNode.mWorldTransform.translate(-10 * delta, 0, 0);
        break;
      }
      case SpeedPaused:
        mClock.setTimeScale(0.0);
        break;
      case SpeedNormal:
        mClock.setTimeScale(1.0);
        break;
      case SpeedFast:
        mClock.setTimeScale(2.0);
        break;
      case SpeedSlow:
        mClock.setTimeScale(0.5);
        break;
      case QuitGame:
        Forge::Log::info << "Exit game\n";
        return false;
      case ToggleFullscreen:
        //mWindow->setFullscreen(!mWindow->isFullscreen());
        break;
      case ToggleDebug:
        Forge::DebugAxis::toggleDebuggingInfo();
        break;
      default:
        break;
    }
  }
  return true;
}

void InGameProcessor::mapDefaultKeys()
{
  using Forge::Key;

  mKeyMap.clear();
  mKeyMap[Key::A] = GameAction::PaddleLeft;
  mKeyMap[Key::D] = GameAction::PaddleRight;
  mKeyMap[Key::Space] = GameAction::ToggleDebug;
  mKeyMap[Key::F] = GameAction::ToggleFullscreen;
  mKeyMap[Key::_0] = GameAction::SpeedPaused;
  mKeyMap[Key::_1] = GameAction::SpeedSlow;
  mKeyMap[Key::_2] = GameAction::SpeedNormal;
  mKeyMap[Key::_3] = GameAction::SpeedFast;
  mKeyMap[Key::Escape] = GameAction::QuitGame;
}

}
