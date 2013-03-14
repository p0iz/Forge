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

#include "lua.hpp"

#include <string>
#include <vector>

namespace Forge {

struct LuaProperties {
	// These reflect the basic types from lua.h
	enum LuaType {
		NONE = -1,
		NIL,
		BOOLEAN,
		LIGHTUSERDATA,
		NUMBER,
		STRING,
		TABLE,
		FUNCTION,
		USERDATA,
		THREAD
	};

	explicit LuaProperties(lua_State*);
	bool hasProperty(const std::string& name);
	LuaType getPropertyType(const std::string& name);

	std::string getString(const std::string& name);
	std::vector<std::string> getStringArray(const std::string& name);

	unsigned int getUnsigned(const std::string& name);
	std::vector<unsigned int> getUnsignedArray(const std::string& name);

	int getInteger(const std::string& name);
	std::vector<int> getIntegerArray(const std::string& name);

	double getNumber(const std::string& name);
	std::vector<double> getNumberArray(const std::string& name);

	float getFloat(const std::string& name);
	std::vector<float> getFloatArray(const std::string& name);

private:
	lua_State* mState;
};

}
