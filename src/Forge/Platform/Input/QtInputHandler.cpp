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

#include "InputHandler.hpp"

Forge::QtInputHandler::~QtInputHandler()
{
}

bool Forge::QtInputHandler::eventFilter(QObject*, QEvent* event)
{
	switch (event->type())
	{
	case QEvent::KeyPress:
		keyPress(static_cast<QKeyEvent*>(event));
		break;
	case QEvent::KeyRelease:
		keyRelease(static_cast<QKeyEvent*>(event));
		break;
	case QEvent::MouseButtonPress:
		mousePress(static_cast<QMouseEvent*>(event));
		break;
	case QEvent::MouseButtonRelease:
		mouseRelease(static_cast<QMouseEvent*>(event));
		break;
	case QEvent::MouseMove:
		mouseMove(static_cast<QMouseEvent*>(event));
		break;
	default:
		return false;
	}
	return true;
}
