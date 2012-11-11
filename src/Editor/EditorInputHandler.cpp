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

#include "EditorInputHandler.h"

#include "Graphics/DebugAxis.h"
#include "Graphics/OrbitalCamera.h"
#include "Graphics/RendererWidget.h"

#include <QKeyEvent>
#include <QMouseEvent>

EditorInputHandler::EditorInputHandler(Forge::OrbitalCamera &camera)
	: mCamera(camera)
{
}

void EditorInputHandler::keyPress(QKeyEvent* event, Forge::RendererWidget* renderer)
{
}

void EditorInputHandler::keyRelease(QKeyEvent* event, Forge::RendererWidget* renderer)
{
}

void EditorInputHandler::mousePress(QMouseEvent *event, Forge::RendererWidget* renderer)
{
}

void EditorInputHandler::mouseRelease(QMouseEvent *event, Forge::RendererWidget* renderer)
{
}

void EditorInputHandler::mouseMove(QMouseEvent *event, Forge::RendererWidget* renderer)
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
		mCamera.updateRotation();
	}
	mPreviousMouseLocation = event->pos();
}
