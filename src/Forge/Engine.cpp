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

#include "Engine.h"

#include "State/EngineState.h"
#include "Graphics/OrbitalCamera.h"
#include "Graphics/RendererWidget.h"
#include "Input/QtInputHandler.h"
#include "Time/HighResClock.h"

namespace Forge {

Engine::Engine(GameStateMachine& stateMachine)
	: mRunning(false),
	  mStateMachine(stateMachine)
{
}

void Engine::start()
{
	if (!mRunning)
	{
		mRunning = true;
		mClock.init();
		mStateMachine.startMachine();
	}
}

void Engine::stop()
{
	if (mRunning)
	{
		mStateMachine.stopMachine();
		mRunning = false;
	}
}

} // namespace Forge
