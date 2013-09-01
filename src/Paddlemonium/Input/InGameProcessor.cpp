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
    Forge::Graphics::RenderWindow& window
  ):
  mInputHandler(Forge::Input::InputHandler::getInstance()),
  mWindow(window),
  mClock(clock),
  mSceneConfig(nullptr),
  mKeyMap()
{
  mapDefaultKeys();
}

InGameProcessor::~InGameProcessor()
{
}

void InGameProcessor::setSceneConfig(Forge::SceneConfig* sceneConfig)
{
  mSceneConfig = sceneConfig;
}

bool InGameProcessor::process(const float delta)
{
  if (!mSceneConfig)
    return true;

  Forge::SceneNode& paddleNode = mSceneConfig->getSceneNode("PaddleNode");

  const double timeScale = mClock.getTimeScale();

  for (Forge::Key key : mInputHandler.getActiveKeys()) {
    if (mKeyMap.count(key) > 0) {
      switch (mKeyMap[key]) {
      case PaddleLeft:
        // Move paddle to the left
        paddleNode.mWorldTransform.translate(MOVE_SPEED * delta * timeScale, 0.0f, 0.0f);
        break;
      case PaddleRight:
        // Move paddle to the right
        paddleNode.mWorldTransform.translate(-MOVE_SPEED * delta * timeScale, 0.0f, 0.0f);
        break;
      case ToggleDebug:
        Forge::DebugAxis::toggleDebuggingInfo();
        // One-shot action
        mInputHandler.injectKeyDown(key);
        break;
      default:
        break;
      }
    }
  }
  processMouseMove();
  return processKeyPress();
}

void InGameProcessor::processMouseMove()
{
  if (!mSceneConfig)
    return;

  const Forge::Camera& camera = mSceneConfig->getCamera();

  Forge::SceneNode& paddleNode = mSceneConfig->getSceneNode("PaddleNode");
  float distance = (camera.getViewMatrix() * paddleNode.mWorldTransform.getMatrix())[3][2];
  float frustumHeight = glm::tan(glm::radians(camera.getFovY() * 0.5f)) * distance;
  float frustumWidth = camera.getAspectRatio() * frustumHeight;

  float percentageX = static_cast<float>(mInputHandler.getMouseX()) / mWindow.width();

  float screenPos = frustumWidth * (2 * percentageX - 1);
  paddleNode.mWorldTransform.setPosition(screenPos, 0.0f, 0.0f);
}

bool InGameProcessor::processKeyPress()
{
  using Forge::Key;

  for (Key key : mInputHandler.getActiveKeys())
  {
    switch (key)
    {
      case Key::_0:
        mClock.setTimeScale(0.0);
        break;
      case Key::_1:
        mClock.setTimeScale(1.0);
        break;
      case Key::_2:
        mClock.setTimeScale(2.0);
        break;
      case Key::_3:
        mClock.setTimeScale(0.5);
        break;
      case Key::Escape:
        Forge::Log::info << "Exit game\n";
        return false;
      case Key::F:
        //mWindow->setFullscreen(!mWindow->isFullscreen());
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
}

}
