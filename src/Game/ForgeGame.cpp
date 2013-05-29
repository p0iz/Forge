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

#include "ForgeGame.h"

#include "State/QtGameState.h"
#include "State/GameStateLibrary.hpp"

#include "Util/Log.h"

#include <QApplication>
#include <QIcon>

ForgeGame::ForgeGame()
	: mForgeConfig("data/game.lua"),
	  mInput(mCamera, mClock),
	  mRenderer(mInput, mCamera)
{
	mInput.setCurrentSceneConfig(&mSceneConfig);
	const Forge::Configuration& cfg = mForgeConfig.getConfig();
	mRenderer.resize(cfg.display.width, cfg.display.height);
	mRenderer.show();
}

void ForgeGame::initializeGameStates()
{
	Forge::GameStatePtr initialState(new Forge::QtGameState(QString("InitialState"),
															mCamera,
															mRenderer,
															mInput,
															mClock,
															mSceneConfig));

	initialState->createStateData();
	Forge::GameStateLibrary::getSingleton().add(initialState->getName(), initialState);
	mStateMachine.init(initialState);
}

void ForgeGame::initializeData()
{
	QIcon icon("data/images/icon128.png");
	mRenderer.setWindowIcon(icon);
}

void ForgeGame::init()
{
	initializeData();
	initializeGameStates();
}

int ForgeGame::run()
{
	int result = 0;
	mClock.init();
	mStateMachine.start();
	result = QApplication::exec();
	mStateMachine.stop();
	return result;
}
