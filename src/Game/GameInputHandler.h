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

#include <map>
#include <set>

namespace Forge {

class HighResClock;
class OrbitalCamera;
class QtRenderer;
class SceneConfig;

} // Forge

enum GameAction
{
	// Camera
	CameraLeft,
	CameraRight,
	CameraForward,
	CameraBack,
	CameraUp,
	CameraDown,

	// Player
	PlayerLeft,
	PlayerRight,
	PlayerForward,
	PlayerBack,
	PlayerUp,
	PlayerDown,

	// Misc.
	ToggleFullscreen,
	ToggleDebug
};

class GameInputHandler : public Forge::QtInputHandler
{
public:
	explicit GameInputHandler(Forge::OrbitalCamera& camera, Forge::HighResClock& clock);
	virtual ~GameInputHandler();
	virtual void keyPress(QKeyEvent* event, Forge::QtRenderer* renderer);
	virtual void keyRelease(QKeyEvent* event, Forge::QtRenderer* renderer);
	virtual void mousePress(QMouseEvent *event, Forge::QtRenderer* renderer);
	virtual void mouseRelease(QMouseEvent *event, Forge::QtRenderer* renderer);
	virtual void mouseMove(QMouseEvent *event, Forge::QtRenderer* renderer);

	virtual void processInput(float delta);

	void setCurrentSceneConfig(Forge::SceneConfig* scene);
private:

	void mapDefaultKeys();

	Forge::OrbitalCamera& mCamera;
	Forge::HighResClock& mClock;

	Forge::SceneConfig* mCurrentSceneConfig;

	QPoint mPreviousMouseLocation;

	std::set<Qt::Key> mCurrentKeys;
	std::map<Qt::Key, GameAction> mKeyActionMap;
};
