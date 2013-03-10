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

namespace Forge {

class OrbitalCamera;
class QtRendererBackend;

} // Forge

class EditorInputHandler : public Forge::QtInputHandler
{
public:
	explicit EditorInputHandler(Forge::OrbitalCamera& camera);
	virtual void keyPress(QKeyEvent* event, Forge::QtRendererBackend* renderer);
	virtual void keyRelease(QKeyEvent* event, Forge::QtRendererBackend* renderer);
	virtual void mousePress(QMouseEvent *event, Forge::QtRendererBackend* renderer);
	virtual void mouseRelease(QMouseEvent *event, Forge::QtRendererBackend* renderer);
	virtual void mouseMove(QMouseEvent *event, Forge::QtRendererBackend* renderer);
private:
	Forge::OrbitalCamera& mCamera;
	QPoint mPreviousMouseLocation;
};
