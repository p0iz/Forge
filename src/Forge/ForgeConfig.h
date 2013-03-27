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

#include "Config/Configuration.hpp"
#include "State/GameStateMachine.hpp"
#include "Time/HighResClock.h"

#include <string>

namespace Forge {

class GameState;

/* This is the main configuration class for the FORGE framework. */
class ForgeConfig
{
public:
	explicit ForgeConfig(const std::string& configFilename = "data/forge.lua");

	const Configuration& getConfig() const {
		return mConfig;
	}

private:
	void loadConfig(const std::string& configFile);
	Configuration mConfig;
};

} // namespace Forge
