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

#include "Input/QtInputHandler.h"

#include <QPoint>

#include <set>

namespace Forge {

class HighResClock;
class OrbitalCamera;
class QtRendererBackend;

} // Forge

enum GameAction
{
	CameraLeft,
	CameraRight,
	CameraForward,
	CameraBack,
	CameraUp,
	CameraDown,
	PlayerLeft,
	PlayerRight,
	PlayerForward,
	PlayerBack,
	PlayerUp,
	PlayerDown
};

class GameInputHandler : public Forge::QtInputHandler
{
public:
	explicit GameInputHandler(Forge::OrbitalCamera& camera, Forge::HighResClock& clock);
	virtual ~GameInputHandler();
	virtual void keyPress(QKeyEvent* event, Forge::QtRendererBackend* renderer);
	virtual void keyRelease(QKeyEvent* event, Forge::QtRendererBackend* renderer);
	virtual void mousePress(QMouseEvent *event, Forge::QtRendererBackend* renderer);
	virtual void mouseRelease(QMouseEvent *event, Forge::QtRendererBackend* renderer);
	virtual void mouseMove(QMouseEvent *event, Forge::QtRendererBackend* renderer);

	virtual void processInput(float delta);
private:
	Forge::OrbitalCamera& mCamera;
	Forge::HighResClock& mClock;

	QPoint mPreviousMouseLocation;

	std::set<GameAction> currentActions;
};
