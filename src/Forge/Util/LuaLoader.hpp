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

#pragma once

#include "Util/Log.h"

#include "lua.hpp"

namespace Forge {

/* A class for loading Lua code
 *
 * This class is used for all kinds of configuration stuff in Forge.
 *
 * The Handler class should implement a 'bool handleLoadedLua(lua_State*)'
 * function that is called after successfully loading the Lua code.
 */
template <class Handler>
class LuaLoader : public Handler {
public:
	bool loadFile(const std::string &file) const;
private:
	/* Helper struct to give Lua state some RAII */
	struct LuaState {
		LuaState() : mState(luaL_newstate()) {
			luaL_openlibs(mState);
		}
		~LuaState() {
			lua_close(mState);
		}
		lua_State* get() {
			return mState;
		}
	private:
		lua_State* mState;
	};
};

template <class Handler>
bool LuaLoader<Handler>::loadFile(const std::string& file) const
{
	bool loaded = false;
	LuaState state;
	lua_State* L = state.get();
	int error = luaL_loadfile(L, file.c_str()) || lua_pcall(L, 0, 0, 0);
	if (error) {
		Log::error << lua_tostring(state.get(), -1) << "\n";
	} else if (Handler::handleLoadedLua(L)) {
		loaded = true;
	} else {
		Log::error << "Failed to load Lua code from file '" << file << "'\n";
	}
	return loaded;
}

}
