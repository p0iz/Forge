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

#include "PaddleGame.h"

#include "State/InGame.h"
#include "State/Menu.h"

// Forge includes
#include "Config/Configuration.hpp"
#include "State/GameStateLibrary.hpp"
#include "Util/Log.h"

#include <QApplication>
#include <QIcon>

namespace Paddlemonium {

PaddleGame::PaddleGame()
	: mInput(mClock, mRenderer)
{
	const Forge::Configuration& cfg = Forge::Configuration::getSingleton();
	cfg.loadConfig("data/PaddleGame.configuration");
	mRenderer.resize(cfg.display.width, cfg.display.height);
	mRenderer.installEventFilter(&mInput);
	mRenderer.show();
}

void PaddleGame::initializeGameStates()
{
	Forge::GameStatePtr menuState(new State::Menu(QString("Menu"),
												  mInput,
												  mClock));
	menuState->createState();

	Forge::GameStatePtr inGameState(new State::InGame(QString("InGame"),
													  mRenderer,
													  mInput,
													  mClock));

	inGameState->createState();

	Forge::GameStateLibrary::getSingleton().add(menuState->getName(), menuState);
	Forge::GameStateLibrary::getSingleton().add(inGameState->getName(), inGameState);
	mStateMachine.init(menuState);
}

void PaddleGame::initializeData()
{
	QIcon icon("data/images/icon128.png");
	mRenderer.setWindowIcon(icon);
}

void PaddleGame::init()
{
	initializeData();
	initializeGameStates();
}

int PaddleGame::run()
{
	Forge::Log::info << "Built on " << __DATE__ << " at " << __TIME__ "\n";

	int result = 0;
	mClock.init();

	mStateMachine.start();

	result = QApplication::exec();

	mStateMachine.stop();

	return result;
}

}
