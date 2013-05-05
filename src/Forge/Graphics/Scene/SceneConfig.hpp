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
 * Copyright 2013 Tommi Martela
 *
 */

#pragma once

#include "SceneNode.hpp"
#include "Graphics/Camera.h"
#include "Graphics/Light/Light.hpp"
#include "Graphics/Material/Material.h"
#include "Graphics/Mesh.h"

#include <unordered_map>
#include <set>
#include <vector>

namespace Forge {

/* This class contains the scene (i.e. level, world chunk, etc.) configuration.
 */
class SceneConfig {
public:
	SceneConfig();

	const SceneNode& getRootSceneNode() const;

	size_t createSceneNode(const std::string& = "");
	void removeSceneNode(size_t id);
	SceneNode& getRootSceneNode();

	// Prefer ID-based searches!
	SceneNode& getSceneNode(const std::string& name);
	SceneNode& getSceneNode(size_t id);
	const SceneNode& getSceneNode(const std::string& name) const;
	const SceneNode& getSceneNode(size_t id) const;

	// Mapping material -> mesh pointer vector
	std::unordered_map<Material, std::vector<MeshPtr>> mMaterialMeshMap;

	// Lights array
	Light lights[Light::MAX_LIGHTS];

	const Camera& getCamera() const;

	// Scene camera
	Camera* mCamera;

	/* This function reorders nodes to create a sorted graph for fast access.
	 * Should only be called when loading a scene. */
	void validateSceneGraph();

	/* This function calculates all world matrices in the current scene graph */
	void calculateWorldTransforms();
private:
	void updateNodeParents(size_t newParent, size_t oldParent);
	std::unordered_set<size_t> collectParents();
	std::vector<size_t> collectChildNodes(size_t parent);
	void swapNodes(size_t node, size_t otherNode);

	std::vector<SceneNode> mNodes;
	SceneNode& mRootNode;
};

} // namespace Forge