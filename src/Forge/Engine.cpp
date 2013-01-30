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
#include "Util/Log.h"

#include <fstream>
#include <sstream>

namespace Forge {

Engine::Engine(GameStateMachine& stateMachine, const char* configFilename)
	: mRunning(false),
	  mStateMachine(stateMachine),
	  mConfigFilename(configFilename)
{
}

void Engine::parseEngineConfig()
{
	std::ifstream configFile(mConfigFilename);
	if (!configFile.is_open())
	{
		Log::error << "Could not open config file: " << mConfigFilename;
		return;
	}
}

void Engine::start()
{
	if (!mRunning)
	{
		Log::info << "Parsing engine config...\n";
		Log::info << "Built on " << __DATE__ << " at " << __TIME__ "\n";
		parseEngineConfig();
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
