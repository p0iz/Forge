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
#include "Util/MaterialParser.h"

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
		std::cout << "Could not open config file: " << mConfigFilename << "\n";
		return;
	}

	enum SectionType
	{
		NONE,
		MATERIAL
	};

	SectionType currentSection = NONE;
	for (std::string configLine; configFile.good(); std::getline(configFile, configLine))
	{
		if (configLine.compare("[Materials]") == 0)
		{
			currentSection = MATERIAL;
		}
		else switch (currentSection)
		{
		case NONE:
			// Skip lines before sections
			break;
		case MATERIAL:
			if (configLine.length() != 0)
			{
				MaterialParser matParser;
				// Parse until next section or EOF
				matParser.parse(configLine);
			}
			break;
		default:
			break;
		}
	}
}

void Engine::start()
{
	if (!mRunning)
	{
		std::cout << "Parsing engine config...\n" << std::flush;
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
