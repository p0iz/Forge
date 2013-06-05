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

#include <QObject>
#include <QInputEvent>
namespace Forge
{

/* Input handler class for Forge projects using Qt.
 * Install as an event handler for widgets that should
 * have event processing. */
class QtInputHandler : public QObject
{
	Q_OBJECT
public:
	virtual ~QtInputHandler();
	bool eventFilter(QObject*, QEvent* event);
	virtual void processInput(float delta) = 0;
private:
	virtual void keyPress(QKeyEvent* event) = 0;
	virtual void keyRelease(QKeyEvent* event) = 0;
	virtual void mousePress(QMouseEvent* event) = 0;
	virtual void mouseRelease(QMouseEvent* event) = 0;
	virtual void mouseMove(QMouseEvent* event) = 0;
};

} // namespace Forge
