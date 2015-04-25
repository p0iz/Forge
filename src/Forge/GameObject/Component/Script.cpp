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
 * Copyright 2014 Tommi Martela
 *
 */

#include "Script.hpp"
#include "ComponentTypes.hpp"
#include "Util/Internal/Keeper.hpp"
#include "Util/Log.h"
#include <lua.hpp>


namespace Forge {

Script::Script(std::string const& scriptFile):
  Component(),
  mScriptFile(scriptFile),
  mState()
{
}

Script::~Script()
{
}

ComponentType Script::getType() const
{
  return ComponentType::Script;
}

void Script::init()
{
  mState.initialize();

  if (mState.isInitialized())
  {
    // Load functions into script Lua state
    Log::info << "Loading script '" << mScriptFile << "'...\n";
    setActive(mState.runScript(mScriptFile));

    if (!mState.hasGlobal("update"))
    {
      Log::error << "Script '" << mScriptFile << "' does not have an update function!\n";
      setActive(false);
    }
  }
}

void Script::update()
{
  // Get thread from pool (blocks if no threads available)
  static std::string UpdateCommand("update()\n");
  mState.runChunk("=Script update", UpdateCommand);
  // Return thread to pool
}

void Script::destroy()
{
}

}
