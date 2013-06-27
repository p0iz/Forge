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

#include "Qt/Input/QtInputHandler.h"

#include <QInputEvent>
#include <QPoint>

#include <map>
#include <set>

namespace Forge {

class HighResClock;
class OrbitalCamera;
class QtRenderer;
class SceneConfig;

} // Forge

namespace Paddlemonium {

enum GameAction
{
	// Paddle
	PaddleLeft,
	PaddleRight,

	// Misc.
	ToggleFullscreen,
	ToggleDebug
};

#ifdef _MSC_VER
template <class ActionType>
class KeyMap : public std::map<Qt::Key, ActionType> { };
#else
template <class ActionType>
using KeyMap = std::map<Qt::Key, ActionType>;
#endif

class InputHandler : public Forge::QtInputHandler
{
public:
	InputHandler(Forge::HighResClock& clock, Forge::QtRenderer& renderer);
	virtual ~InputHandler();

	virtual void processInput(float delta);

	bool isKeyDown(Qt::Key key);

	void setSceneConfig(Forge::SceneConfig* scene);
private:
	virtual void keyPress(QKeyEvent* event);
	virtual void keyRelease(QKeyEvent* event);
	virtual void mousePress(QMouseEvent* event);
	virtual void mouseRelease(QMouseEvent* event);
	virtual void mouseMove(QMouseEvent* event);

	void mapDefaultKeys();

	Forge::HighResClock& mClock;
	Forge::SceneConfig* mSceneConfig;
	Forge::QtRenderer& mRenderer;

	QPoint mPreviousMouseLocation;

	std::set<Qt::Key> mCurrentKeys;
	KeyMap<GameAction> mKeyActionMap;
};

}
