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
#include <QInputEvent>

namespace Forge {

class OrbitalCamera;
class QtRenderer;

} // Forge

class EditorInputHandler : public Forge::QtInputHandler
{
public:
	explicit EditorInputHandler(Forge::OrbitalCamera& camera);
	virtual bool eventFilter(QObject *widget, QEvent *event);
	virtual void processInput(float delta);
private:
	void keyPress(QKeyEvent* event);
	void keyRelease(QKeyEvent* event);
	void mousePress(QMouseEvent* event);
	void mouseRelease(QMouseEvent* event);
	void mouseMove(QMouseEvent* event);

	Forge::OrbitalCamera& mCamera;
	QPoint mPreviousMouseLocation;
};
