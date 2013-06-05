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

#include "State/InGame.h"
#include "State/GameStateLibrary.hpp"

#include "Input/QtInputHandler.h"
#include "Graphics/Loaders/MeshLoader.h"
#include "Graphics/Material/Technique/InternalTechniques.hpp"
#include "Graphics/QtRenderer.hpp"
#include "Time/HighResClock.h"
#include "Util/Log.h"

#include <sstream>

namespace Paddlemonium { namespace State {

InGame::InGame(const QString& name,
						 Forge::Camera& camera,
						 Forge::QtRenderer& renderer,
						 InputHandler& input,
						 Forge::HighResClock& clock)
	: GameState(name.toStdString()),
	  mInput(input),
	  mCamera(camera),
	  mRenderer(renderer),
	  mClock(clock) { }

Forge::GameStatePtr InGame::frameUpdate() {
	static Forge::GameStateLibrary& library = Forge::GameStateLibrary::getSingleton();

	// Update clock
	mClock.updateDeltaTime();
	float delta = mClock.getGameDelta();

	// Process input
	mInput.processInput(delta);

	// Render
	mRenderer.render(mSceneConfig);

	// Return next (this) state
	if (mInput.isKeyDown(Qt::Key_Space)) {
		// Return paused state
	}
	return library.get(getName());
}

void InGame::createState() {
	// Create game view
	mPaddleMesh = Forge::MeshLoader::loadMesh("data/paddle.obj");
	mPaddleNode = mSceneConfig.createSceneNode("PaddleNode");
	mPaddleMesh->attachToNode(mPaddleNode);

	mTileMesh = Forge::MeshLoader::loadMesh("data/tile.obj");
	mTileNode = mSceneConfig.createSceneNode("TileNode");
	mTileMesh->attachToNode(mTileNode);

	// Done. Allow the scene config to manipulate the scene
	mSceneConfig.setCamera(mCamera);
	mInput.setSceneConfig(&mSceneConfig);
}

void InGame::destroyState() {
	// Destroy game view
}

}}
