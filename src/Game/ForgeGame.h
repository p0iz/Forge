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

#include "GameInputHandler.h"

#include "Engine.h"
#include "Graphics/OrbitalCamera.h"
#include "Graphics/RendererWidget.h"
#include "State/QtEngineState.h"
#include "State/QtGameStateMachine.hpp"

class ForgeGame
{
public:
	ForgeGame();
	void init();
	int run();

private:
	Forge::Engine mEngine;

	GameInputHandler mInput;

	Forge::QtGameStateMachine mStateMachine;

	Forge::OrbitalCamera mCamera;

	Forge::RendererWidget mRenderer;

	Forge::QtEngineState mInitialState;
};
