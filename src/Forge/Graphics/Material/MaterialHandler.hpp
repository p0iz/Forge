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

#include "Technique/Technique.h"

struct lua_State;

namespace Forge {

class Material;
class TechniqueLibrary;

struct MaterialHandler {
	MaterialHandler();
	void setTargetMaterial(Material* material);
	void setTechniqueLibrary(const TechniqueLibrary& techLibrary);
protected:
	bool handleLoadedLua(lua_State* state) const;
private:
	// Encapsulate the internal Lua state
	TechniquePtr loadTechnique(lua_State* state) const;
	bool loadProperties(lua_State* state, TechniquePtr technique) const;

	Material* mTargetMaterial;
	const TechniqueLibrary* mTechLibrary;
};

}
