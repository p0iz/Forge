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

#include "Graphics/Light/Light.hpp"
#include "Graphics/Scene/SceneConfig.hpp"
#include "Graphics/Material/Material.h"
#include "Graphics/Material/Technique/TechniqueLibrary.h"
#include "State/GameState.h"
#include "Time/HighResClock.h"

#include "Qt/Graphics/QtRenderer.hpp"

#include <memory>

namespace Forge
{
	class QtInputHandler;

	class QtGameState : public QObject, public GameState
	{
		Q_OBJECT
	public:
		QtGameState(
				const QString& name,
				Camera& camera,
				QtRenderer& renderer,
				QtInputHandler& input,
				HighResClock& clock,
				SceneConfig& config);
		virtual GameStatePtr frameUpdate();

		virtual void createState();
		virtual void destroyState();

	private:
		void createTestScene();
		void createSceneGraph();

		Camera& mCamera;
		QtRenderer& mRenderer;
		QtInputHandler& mInput;
		HighResClock& mClock;

		// Technique library
		TechniqueLibrary mTechniqueLibrary;

		SceneConfig& mSceneConfig;

		// Materials
		Material mCubeMaterial;
		Material mLampMaterial;
		Material mRoomMaterial;

		// Scene nodes
		SceneNodeId mRoomNodeId;
		enum { CUBE_NODES = 10 };
		SceneNodeId mCubeNodes[CUBE_NODES];

		SceneNodeId mPlayerNode;
		SceneNodeId mPaddleNode;
	};
} // namespace Forge
