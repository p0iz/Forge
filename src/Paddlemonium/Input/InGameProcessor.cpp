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

#include <map>

#include <X11/keysym.h>


namespace Paddlemonium {

// TODO: Make a config with this stuff
namespace {
  const int MOVE_SPEED = 10.0f;
}

InGameProcessor::InGameProcessor():
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

void InGameProcessor::process(const float delta, Forge::Input::InputHandler const& handler)
{
//  if (!mSceneConfig)
//    return;

//  Forge::SceneNode& paddleNode = mSceneConfig->getSceneNode("PaddleNode");

//  const double timeScale = mClock.getTimeScale();

//  for (Qt::Key key : mCurrentKeys) {
//    if (mKeyActionMap.count(key) > 0) {
//      switch (mKeyActionMap[key]) {
//      case PaddleLeft:
//        // Move paddle to the left
//        paddleNode.mWorldTransform.translate(MOVE_SPEED * delta * timeScale, 0.0f, 0.0f);
//        break;
//      case PaddleRight:
//        // Move paddle to the right
//        paddleNode.mWorldTransform.translate(-MOVE_SPEED * delta * timeScale, 0.0f, 0.0f);
//        break;
//      case ToggleDebug:
//        Forge::DebugAxis::toggleDebuggingInfo();
//        // One-shot action
//        mCurrentKeys.erase(key);
//        break;
//      default:
//        break;
//      }
//    }
  //  }
}

void InGameProcessor::processMouseMove()
{
//  if (!mSceneConfig)
//    return;

//  const Forge::Camera& camera = mSceneConfig->getCamera();

//  Forge::SceneNode& paddleNode = mSceneConfig->getSceneNode("PaddleNode");
//  float distance = (camera.getViewMatrix() * paddleNode.mWorldTransform.getMatrix())[3][2];
//  float frustumHeight = glm::tan(glm::radians(camera.getFovY() * 0.5f)) * distance;
//  float frustumWidth = camera.getAspectRatio() * frustumHeight;

//  float percentageX = (event->windowPos().x() / mRenderer.width());

//  float screenPos = frustumWidth * (2 * percentageX - 1);
//  paddleNode.mWorldTransform.setPosition(screenPos, 0.0f, 0.0f);
  //  mPreviousMouseLocation = event->pos();
}

void InGameProcessor::processKeyPress()
{
//  switch (event->key())
//  {
//  case Qt::Key_0:
//    mClock.setTimeScale(0.0);
//    break;
//  case Qt::Key_1:
//    mClock.setTimeScale(1.0);
//    break;
//  case Qt::Key_2:
//    mClock.setTimeScale(2.0);
//    break;
//  case Qt::Key_3:
//    mClock.setTimeScale(0.5);
//    break;
//  case Qt::Key_Escape:
//    mRenderer.close();
//    break;
//  case Qt::Key_F:
//    //mRenderer.toggleFullscreen();
//    mRenderWindow->setFullscreen(!mRenderWindow->isFullscreen());
//    break;
//  default:
//    mCurrentKeys.insert(static_cast<Qt::Key>(event->key()));
//  }
}

void InGameProcessor::mapDefaultKeys()
{
  mKeyMap.clear();
  mKeyMap['a'] = GameAction::PaddleLeft;
  mKeyMap['d'] = GameAction::PaddleRight;
  mKeyMap[' '] = GameAction::ToggleDebug;
  mKeyMap['f'] = GameAction::ToggleFullscreen;
}

}
