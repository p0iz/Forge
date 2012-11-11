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

#include "Util/Log.h"
#include "Util/MaterialParser.h"

#include <QApplication>
#include <QIcon>

ForgeGame::ForgeGame()
	: mEngine(mStateMachine),
	  mInput(mCamera, mEngine.getGameClock()),
	  mRenderer(mCamera, mInput),
	  mInitialState(mRenderer, mInput, mEngine.getGameClock())
{
}

void ForgeGame::init()
{
	Log().info() << "Initializing...\n";
	mRenderer.setCamera(mCamera);
	mStateMachine.setCurrentState(&mInitialState);

	Forge::MaterialParser parser("./data/Material.xml");
	parser.parse();

	Log().info() << "Setting icon...\n";
	QIcon icon("data/images/icon128.png");
	mRenderer.setWindowIcon(icon);

	Log().info() << "Initialization done.\n";
}

int ForgeGame::run()
{
	int result = 0;
	mRenderer.show();
	mStateMachine.setCurrentState(&mInitialState);
	mEngine.start();
	result = QApplication::exec();
	mEngine.stop();
	return result;
}
