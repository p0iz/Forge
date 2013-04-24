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

#include "State/QtStateMachine.hpp"
#include "State/QtGameState.h"

void Forge::QtStateMachine::start(int frameDelay)
{
	QObject::connect(&mFrameTimer, SIGNAL(timeout()), this, SLOT(fireCurrentState()));
	mFrameTimer.start(frameDelay);
}

void Forge::QtStateMachine::stop()
{
	mFrameTimer.stop();
	QObject::disconnect(&mFrameTimer, SIGNAL(timeout()), this, SLOT(fireCurrentState()));
	mStateMachine.reset();
}

void Forge::QtStateMachine::fireCurrentState()
{
	if (!mStateMachine.update()) {
		stop();
	}
}


void Forge::QtStateMachine::init(const Forge::GameStatePtr& initialState) {
	mStateMachine.init(initialState);
}
