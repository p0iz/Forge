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

#include "Input/InputHandler.h"

// Forge includes
#include "Graphics/Light/Light.hpp"
#include "Graphics/QtRenderer.hpp"
#include "Graphics/Scene/SceneConfig.hpp"
#include "Graphics/Material/Material.h"
#include "Graphics/Material/Technique/TechniqueLibrary.h"
#include "State/GameState.h"
#include "Time/HighResClock.h"

#include <memory>

namespace Paddlemonium { namespace State {

class Menu : public QObject, public Forge::GameState
{
	Q_OBJECT
public:
	Menu(const QString& name,
				InputHandler& input,
				Forge::HighResClock& clock);

	virtual Forge::GameStatePtr frameUpdate();
	virtual void createState();
	virtual void destroyState();

private:
	Paddlemonium::InputHandler& mInput;
	Forge::HighResClock& mClock;
};

}}
