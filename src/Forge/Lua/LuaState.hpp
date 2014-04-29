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

#include "ForgeExport.h"
#include "LuaForwardDeclarations.hpp"
#include <iosfwd>


namespace Forge {

class Application;

class LuaClass;

class LuaLibrary;

class FORGE_EXPORT LuaState
{
  public:
    LuaState(Application& app);
    ~LuaState();

    bool initialize();

    bool isInitialized() const;

    void addClass(LuaClass&& klass);

    void importLibrary(LuaLibrary&& library);

    void removeLibrary(LuaLibrary&& library);

    bool runScript(std::string const& scriptFile);

    bool isIncompleteChunk(std::string const& chunk);

    bool runChunk(const std::string& programName, std::string const& chunk);

    bool hasGlobal(std::string const& name) const;

  private:
    Application& mApp;
    lua_State* mState;
};

}
