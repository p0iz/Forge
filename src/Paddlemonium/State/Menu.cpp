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

#include "State/Menu.h"
#include "State/GameStateLibrary.hpp"

#include "Graphics/Loaders/MeshLoader.h"
#include "Graphics/Material/Technique/InternalTechniques.hpp"
#include "Time/HighResClock.h"
#include "Util/Log.h"

#include "Qt/Graphics/QtRenderer.hpp"
#include "Qt/Input/QtInputHandler.h"

#include <sstream>

namespace Paddlemonium { namespace State {

Menu::Menu(const QString& name,
		   InputHandler& input,
		   Forge::HighResClock& clock)
	: GameState(name.toStdString()),
	  mInput(input),
	  mClock(clock) { }

Forge::GameStatePtr Menu::frameUpdate() {
	static Forge::GameStateLibrary& library = Forge::GameStateLibrary::getSingleton();

	// Update clock
	mClock.updateDeltaTime();
	float delta = mClock.getGameDelta();

	// Process input
	mInput.processInput(delta);

	// Return next (this) state
	Forge::Log::info << "Starting game.\n";
	return library.get("InGame");
}

void Menu::createState() {
}

void Menu::destroyState() { }

}}
