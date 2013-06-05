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

#include "Input/InputHandler.h"

#include "Graphics/DebugAxis.h"
#include "Graphics/OrbitalCamera.h"
#include "Graphics/QtRenderer.hpp"
#include "Graphics/Scene/Transformation.hpp"

#include "Time/HighResClock.h"

#include "Util/Log.h"
#include "Util/Exceptions.hpp"

#include <QKeyEvent>
#include <QMouseEvent>

#include <iostream>

namespace {
	const int MOVE_SPEED = 1.0f;
}

namespace Paddlemonium {

InputHandler::InputHandler(Forge::HighResClock& clock, Forge::QtRenderer& renderer)
	: mClock(clock), mSceneConfig(nullptr), mRenderer(renderer)
{
	mapDefaultKeys();
}

InputHandler::~InputHandler()
{
}

void InputHandler::keyPress(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_0:
		mClock.setTimeScale(0.0);
		break;
	case Qt::Key_1:
		mClock.setTimeScale(1.0);
		break;
	case Qt::Key_2:
		mClock.setTimeScale(2.0);
		break;
	case Qt::Key_3:
		mClock.setTimeScale(0.5);
		break;
	case Qt::Key_Escape:
		mRenderer.close();
		break;
	case Qt::Key_F:
		mRenderer.toggleFullscreen();
		break;
	default:
		mCurrentKeys.insert(static_cast<Qt::Key>(event->key()));
	}
}

void InputHandler::keyRelease(QKeyEvent* event)
{
	mCurrentKeys.erase(static_cast<Qt::Key>(event->key()));
}

void InputHandler::mousePress(QMouseEvent *event)
{
}

void InputHandler::mouseRelease(QMouseEvent *event)
{
}

void InputHandler::mouseMove(QMouseEvent *event)
{
	Forge::SceneNode& paddleNode = mSceneConfig->getSceneNode("PaddleNode");
	QPoint relativeMovement = event->pos() - mPreviousMouseLocation;
	if (mSceneConfig) {
		// Move paddle
		try {
			paddleNode.mWorldTransform.translate(relativeMovement.x() * 0.1f,
										   0.0f,
										   0.0f);
		} catch (Forge::NotFoundException exception) {
			Forge::Log::error << "Could not find scene node '" << exception.missing << "'\n";
		}
	}
	mPreviousMouseLocation = event->pos();
}

void InputHandler::processInput(float delta)
{
	if (!mSceneConfig)
		return;

	Forge::SceneNode& paddleNode = mSceneConfig->getSceneNode("PaddleNode");

	const double timeScale = mClock.getTimeScale();

	for (Qt::Key key : mCurrentKeys) {
		if (mKeyActionMap.count(key) > 0) {
			switch (mKeyActionMap[key]) {
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
				mCurrentKeys.erase(key);
				break;
			default:
				break;
			}
		}
	}
}

bool InputHandler::isKeyDown(Qt::Key key)
{
	return mCurrentKeys.count(key);
}

void InputHandler::setSceneConfig(Forge::SceneConfig* scene)
{
	mSceneConfig = scene;
}

void InputHandler::mapDefaultKeys()
{
	mKeyActionMap[Qt::Key_Left] = PaddleLeft;
	mKeyActionMap[Qt::Key_Right] = PaddleRight;
	mKeyActionMap[Qt::Key_Space] = ToggleDebug;
	mKeyActionMap[Qt::Key_F] = ToggleFullscreen;
}

}
