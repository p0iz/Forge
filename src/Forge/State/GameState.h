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

#include <memory>
#include <string>

namespace Forge
{

struct GameState {
	explicit GameState(const std::string& name);
	virtual ~GameState();
	virtual void enter();
	virtual std::shared_ptr<GameState> frameUpdate();

	/* Calling these two functions is left to the users' discretion */
	virtual void createState();
	virtual void destroyState();

	const std::string& getName() const;
private:
	std::string mName;
};

typedef std::shared_ptr<GameState> GameStatePtr;

} // namespace Forge
