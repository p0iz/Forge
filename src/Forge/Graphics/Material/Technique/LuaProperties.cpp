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

#include "LuaProperties.hpp"

#include "Util/Log.h"

#include "lua.hpp"

#include <cassert>

namespace Forge {

LuaProperties::LuaProperties(lua_State* state) : mState(state) {
	assert(lua_istable(state, -1));
}

bool LuaProperties::hasProperty(const std::string& name) {
	lua_getfield(mState, -1, name.c_str());
	bool exists = not lua_isnoneornil(mState, -1);
	lua_pop(mState, 1);
	return exists;
}

LuaProperties::LuaType LuaProperties::getPropertyType(const std::string& name) {
	lua_getfield(mState, -1, name.c_str());
	LuaType type = static_cast<LuaType>(lua_type(mState, -1));
	lua_pop(mState, 1);
	return type;
}

std::string LuaProperties::getString(const std::string& name) {
	const char* property = nullptr;
	lua_getfield(mState, -1, name.c_str());
	if (lua_isstring(mState, -1)) {
		property = lua_tostring(mState, -1);
	}
	lua_pop(mState, 1);
	return property;
}

std::vector<std::string> LuaProperties::getStringArray(const std::string& name) {
	std::vector<std::string> property;
	if (luaL_getsubtable(mState, -1, name.c_str())) {
		lua_pushnil(mState);
		while (lua_next(mState, -2)) {
			if (lua_isstring(mState, -1)) {
				property.push_back(lua_tostring(mState, -1));
				lua_pop(mState, 1);
			} else {
				Log::error << "Encountered a non-string while parsing string array '"
						   << name << "'!\n";
				lua_pop(mState, 1);
			}
		}
		lua_pop(mState, 1);
	}
	return property;
}

unsigned int LuaProperties::getUnsigned(const std::string& name) {
	unsigned int property = 0;
	lua_getfield(mState, -1, name.c_str());
	if (lua_isnumber(mState, -1)) {
		property = lua_tounsigned(mState, -1);
	}
	lua_pop(mState, 1);
	return property;
}

std::vector<unsigned int> LuaProperties::getUnsignedArray(const std::string& name) {
	std::vector<unsigned int> property;
	if (luaL_getsubtable(mState, -1, name.c_str())) {
		lua_pushnil(mState);
		while (lua_next(mState, -2)) {
			if (lua_isnumber(mState, -1)) {
				property.push_back(lua_tounsigned(mState, -1));
				lua_pop(mState, 1);
			} else {
				Log::error << "Encountered a non-number while parsing numeric array '"
						   << name << "'!\n";
				lua_pop(mState, 1);
			}
		}
		lua_pop(mState, 1);
	}
	return property;
}

int LuaProperties::getInteger(const std::string& name) {
	int property = -1;
	lua_getfield(mState, -1, name.c_str());
	if (lua_isnumber(mState, -1)) {
		property = lua_tointeger(mState, -1);
	}
	lua_pop(mState, 1);
	return property;
}

std::vector<int> LuaProperties::getIntegerArray(const std::string& name) {
	std::vector<int> property;
	if (luaL_getsubtable(mState, -1, name.c_str())) {
		lua_pushnil(mState);
		while (lua_next(mState, -2)) {
			if (lua_isnumber(mState, -1)) {
				property.push_back(lua_tointeger(mState, -1));
				lua_pop(mState, 1);
			} else {
				Log::error << "Encountered a non-number while parsing numeric array '"
						   << name << "'!\n";
				lua_pop(mState, 1);
			}
		}
		lua_pop(mState, 1);
	}
	return property;
}

double LuaProperties::getNumber(const std::string& name) {
	double property = 0.0f;
	lua_getfield(mState, -1, name.c_str());
	if (lua_isnumber(mState, -1)) {
		property = lua_tonumber(mState, -1);
	}
	lua_pop(mState, 1);
	return property;
}

std::vector<double> LuaProperties::getNumberArray(const std::string& name) {
	std::vector<double> property;
	if (luaL_getsubtable(mState, -1, name.c_str())) {
		lua_pushnil(mState);
		while (lua_next(mState, -2)) {
			if (lua_isnumber(mState, -1)) {
				property.push_back(lua_tonumber(mState, -1));
				lua_pop(mState, 1);
			} else {
				Log::error << "Encountered a non-number while parsing numeric array '"
						   << name << "'!\n";
				lua_pop(mState, 1);
			}
		}
		lua_pop(mState, 1);
	}
	return property;
}

float LuaProperties::getFloat(const std::string& name) {
	float property = 0.0f;
	lua_getfield(mState, -1, name.c_str());
	if (lua_isnumber(mState, -1)) {
		property = lua_tonumber(mState, -1);
	}
	lua_pop(mState, 1);
	return property;
}

std::vector<float> LuaProperties::getFloatArray(const std::string& name) {
	std::vector<float> property;
	if (luaL_getsubtable(mState, -1, name.c_str())) {
		lua_pushnil(mState);
		while (lua_next(mState, -2)) {
			if (lua_isnumber(mState, -1)) {
				property.push_back(lua_tonumber(mState, -1));
			} else {
				Log::error << "Encountered a non-number while parsing numeric array '"
						   << name << "'!\n";
			}
			lua_pop(mState, 1);
		}
		lua_pop(mState, 1);
	}
	return property;
}

}
