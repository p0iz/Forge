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
 * Copyright 2013 Tommi Martela
 *
 */

#include "ConfigHandler.hpp"

#include "Configuration.hpp"
#include "Util/Log.h"

#include "lua.hpp"

namespace Forge {

bool ConfigHandler::handleLoadedLua(lua_State* state) const
{
	bool loaded = false;

	Configuration& config = Configuration::getSingleton();

	lua_getglobal(state, "width");
	lua_getglobal(state, "height");
	if (lua_isnumber(state, -2) && lua_isnumber(state, -1)) {
		config.display.width = static_cast<int>(lua_tonumber(state, -2));
		config.display.height = static_cast<int>(lua_tonumber(state, -1));
		loaded = true;
	} else {
		Log::error << "Config error: display parameters should be numbers!\n";
	}
	return loaded;
}

}
