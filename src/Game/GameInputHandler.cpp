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
#include "Graphics/QtRendererBackend.hpp"

#include "Time/HighResClock.h"

#include "Util/Log.h"

#include <QKeyEvent>
#include <QMouseEvent>

#include <iostream>

GameInputHandler::GameInputHandler(Forge::OrbitalCamera& camera, Forge::HighResClock& clock)
	: mCamera(camera), mClock(clock)
{
}

GameInputHandler::~GameInputHandler()
{
}

void GameInputHandler::keyPress(QKeyEvent* event, Forge::QtRendererBackend* renderer)
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
	case Qt::Key_W:
		currentActions.insert(CameraForward);
		break;
	case Qt::Key_S:
		currentActions.insert(CameraBack);
		break;
	case Qt::Key_A:
		currentActions.insert(CameraLeft);
		break;
	case Qt::Key_D:
		currentActions.insert(CameraRight);
		break;
	case Qt::Key_Space:
		Forge::DebugAxis::toggleDebuggingInfo();
		break;
	case Qt::Key_F:
		renderer->toggleFullscreen();
		break;
	case Qt::Key_Q:
	case Qt::Key_Escape:
		renderer->close();
		break;
	}
}

void GameInputHandler::keyRelease(QKeyEvent* event, Forge::QtRendererBackend* renderer)
{
	switch (event->key())
	{
	case Qt::Key_1:

	case Qt::Key_W:
		currentActions.erase(CameraForward);
		break;
	case Qt::Key_S:
		currentActions.erase(CameraBack);
		break;
	case Qt::Key_A:
		currentActions.erase(CameraLeft);
		break;
	case Qt::Key_D:
		currentActions.erase(CameraRight);
		break;
	}
}

void GameInputHandler::mousePress(QMouseEvent *event, Forge::QtRendererBackend* renderer)
{
}

void GameInputHandler::mouseRelease(QMouseEvent *event, Forge::QtRendererBackend* renderer)
{
}

void GameInputHandler::mouseMove(QMouseEvent *event, Forge::QtRendererBackend* renderer)
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
	for (GameAction action : currentActions)
	{
		glm::vec2 translation;
		const double timeScale = mClock.getTimeScale();
		switch (action)
		{
		case CameraLeft:
			translation.x -= 2.0f * delta * timeScale;
			break;
		case CameraRight:
			translation.x += 2.0f * delta * timeScale;
			break;
		case CameraForward:
			translation.y -= 2.0f * delta * timeScale;
			break;
		case CameraBack:
			translation.y += 2.0f * delta * timeScale;
			break;
		default:
			break;
		}
		glm::vec3 rotation(mCamera.getRotation());
		glm::vec3 targetTranslation(
					translation.x * sin(rotation.x) + translation.y * cos(rotation.x),
					0.0f,
					translation.y * sin(rotation.x) - translation.x * cos(rotation.x));
		mCamera.updatePosition(targetTranslation);
	}
}
