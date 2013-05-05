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

#include "State/GameStateLibrary.hpp"

void Forge::GameStateLibrary::add(const std::string& name, Forge::GameStatePtr state)
{
	mGameStates.insert(std::pair<std::string, Forge::GameStatePtr>(name, state));
}

Forge::GameStatePtr Forge::GameStateLibrary::get(const std::string& name)
{
	return mGameStates[name];
}
