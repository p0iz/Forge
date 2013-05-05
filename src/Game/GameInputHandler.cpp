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

#include "GameInputHandler.h"

#include "Graphics/DebugAxis.h"
#include "Graphics/OrbitalCamera.h"
#include "Graphics/QtRenderer.hpp"
#include "Graphics/Scene/Transformation.hpp"

#include "Time/HighResClock.h"

#include "Util/Log.h"

#include <QKeyEvent>
#include <QMouseEvent>

#include <iostream>

namespace {
	const int MOVE_SPEED = 1.0f;
}

GameInputHandler::GameInputHandler(Forge::OrbitalCamera& camera, Forge::HighResClock& clock)
	: mCamera(camera), mClock(clock), mCurrentSceneConfig(nullptr)
{
	mapDefaultKeys();
}

GameInputHandler::~GameInputHandler()
{
}

void GameInputHandler::keyPress(QKeyEvent* event, Forge::QtRenderer* renderer)
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
		renderer->close();
		break;
	case Qt::Key_F:
		renderer->toggleFullscreen();
		break;
	default:
		mCurrentKeys.insert(static_cast<Qt::Key>(event->key()));
	}
}

void GameInputHandler::keyRelease(QKeyEvent* event, Forge::QtRenderer* renderer)
{
	mCurrentKeys.erase(static_cast<Qt::Key>(event->key()));
}

void GameInputHandler::mousePress(QMouseEvent *event, Forge::QtRenderer* renderer)
{
}

void GameInputHandler::mouseRelease(QMouseEvent *event, Forge::QtRenderer* renderer)
{
}

void GameInputHandler::mouseMove(QMouseEvent *event, Forge::QtRenderer* renderer)
{
	QPoint relativeMovement = event->pos() - mPreviousMouseLocation;
	if (event->buttons() & Qt::LeftButton)
	{
		float yaw = 0, pitch = 0;
		if (event->modifiers() & Qt::AltModifier)
		{
			float horizontalMove = -relativeMovement.x() * 0.02f;
			float verticalMove = -relativeMovement.y() * 0.02f;

			glm::vec3 rotation(mCamera.getRotation());
			glm::vec3 targetTranslation(
						horizontalMove * sin(rotation.x) + verticalMove * cos(rotation.x),
						0.0f,
						verticalMove * sin(rotation.x) - horizontalMove * cos(rotation.x));

			mCamera.updatePosition(glm::vec3(targetTranslation));
		}
		else
		{
			yaw = relativeMovement.x();
			pitch = -relativeMovement.y();
		}
		mCamera.updateRotation(yaw, pitch);
	}
	if (event->buttons() & Qt::RightButton)
	{
		mCamera.setRadius(mCamera.getRadius() + (event->y() - mPreviousMouseLocation.y()) * 0.01f);
	}
	mPreviousMouseLocation = event->pos();
}

void GameInputHandler::processInput(float delta)
{
	for (Qt::Key key : mCurrentKeys)
	{
		if (mKeyActionMap.count(key) < 1) {
			// Nothing mapped to this key
			continue;
		}
		glm::vec2 cameraTranslation;
		Forge::Transformation playerTransformation;
		const double timeScale = mClock.getTimeScale();
		switch (mKeyActionMap[key])
		{
		case CameraLeft:
			cameraTranslation.x -= MOVE_SPEED * delta * timeScale;
			break;
		case CameraRight:
			cameraTranslation.x += MOVE_SPEED * delta * timeScale;
			break;
		case CameraForward:
			cameraTranslation.y -= MOVE_SPEED * delta * timeScale;
			break;
		case CameraBack:
			cameraTranslation.y += MOVE_SPEED * delta * timeScale;
			break;
		case PlayerLeft:
			playerTransformation.rotate(-MOVE_SPEED * delta * timeScale, glm::vec3(0,1,0));
			break;
		case PlayerRight:
			playerTransformation.rotate(MOVE_SPEED * delta * timeScale, glm::vec3(0,1,0));
			break;
		case PlayerForward:
			playerTransformation.translate(0.0f, 0.0f, -MOVE_SPEED * delta * timeScale);
			break;
		case PlayerBack:
			playerTransformation.translate(0.0f, 0.0f, MOVE_SPEED * delta * timeScale);
			break;
		case ToggleDebug:
			Forge::DebugAxis::toggleDebuggingInfo();
			// One-shot action
			mCurrentKeys.erase(key);
			break;
		default:
			break;
		}
		glm::vec3 rotation(mCamera.getRotation());
		glm::vec3 targetTranslation(
					cameraTranslation.x * sin(rotation.x) + cameraTranslation.y * cos(rotation.x),
					0.0f,
					cameraTranslation.y * sin(rotation.x) - cameraTranslation.x * cos(rotation.x));
		mCamera.updatePosition(targetTranslation);
	}
}

void GameInputHandler::setCurrentSceneConfig(Forge::SceneConfig* scene)
{
	mCurrentSceneConfig = scene;
}

void GameInputHandler::mapDefaultKeys()
{
	mKeyActionMap[Qt::Key_W] = CameraForward;
	mKeyActionMap[Qt::Key_S] = CameraBack;
	mKeyActionMap[Qt::Key_A] = CameraLeft;
	mKeyActionMap[Qt::Key_D] = CameraRight;
	mKeyActionMap[Qt::Key_Up] = PlayerForward;
	mKeyActionMap[Qt::Key_Down] = PlayerBack;
	mKeyActionMap[Qt::Key_Left] = PlayerLeft;
	mKeyActionMap[Qt::Key_Right] = PlayerRight;
	mKeyActionMap[Qt::Key_Space] = ToggleDebug;
	mKeyActionMap[Qt::Key_F] = ToggleFullscreen;
}
