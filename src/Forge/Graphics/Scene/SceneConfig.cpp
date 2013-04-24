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

#include "SceneConfig.hpp"

#include "Util/Exceptions.hpp"
#include "Util/Log.h"

#include <algorithm>
#include <string>

namespace Forge {

SceneConfig::SceneConfig()
	: mNodes(1, SceneNode("Root Node")), mRootNode(mNodes[0]) { }

void SceneConfig::removeSceneNode(size_t id)
{
	auto iterator = mNodes.begin()+id;
	mNodes.erase(iterator);
	for (size_t current = id; current < mNodes.size(); ++current) {
		if (mNodes[current].mParent >= id) {
			--mNodes[current].mParent;
		}
	}
}

SceneNode& SceneConfig::getRootSceneNode()
{
	return mRootNode;
}

SceneNode& SceneConfig::getSceneNode(const std::string& name) {
	auto iter = std::find_if(mNodes.begin(),
							 mNodes.end(),
							 [&name](const SceneNode& node) { return node.mName == name; });
	if (iter != mNodes.end()) {
		return *iter;
	} else {
		throw NotFoundException(name);
	}
}

SceneNode& SceneConfig::getSceneNode(size_t id) {
	return mNodes[id];
}

const SceneNode& SceneConfig::getSceneNode(const std::string& name) const {
	auto iter = std::find_if(mNodes.begin(),
							 mNodes.end(),
							 [name](const SceneNode& node) { return node.mName == name; });
	if (iter != mNodes.end()) {
		return *iter;
	} else {
		throw NotFoundException(name);
	}
}

const SceneNode& SceneConfig::getSceneNode(size_t id) const {
	return mNodes[id];
}

const Camera& SceneConfig::getCamera() const
{
	return *mCamera;
}

void SceneConfig::validateSceneGraph()
{
	// Collect all parent nodes
	std::unordered_set<size_t> parents = collectParents();

	// For each parent node, verify that all children are after it in the vector
	for (size_t parent : parents) {
		std::vector<size_t> childNodes = collectChildNodes(parent);
		size_t newParentPosition = parent;

		for (size_t node : childNodes) {
			if (node < parent) {
				// Move node after parent and update the nodes in open range ]node, parent[
				swapNodes(node, parent);
				newParentPosition = node;
			}
		}
		updateNodeParents(newParentPosition, parent);
	}
}

void SceneConfig::calculateWorldTransforms()
{
	for (SceneNode& node : mNodes) {
		node.mWorldTransform.applyMatrix(mNodes[node.mParent].mWorldTransform.getMatrix());
	}
}

void SceneConfig::updateNodeParents(size_t newParent, size_t oldParent) {
	for (SceneNode& node : mNodes) {
		if (node.mParent == oldParent) {
			node.mParent = newParent;
		}
	}
}

std::unordered_set<size_t> SceneConfig::collectParents()
{
	std::unordered_set<size_t> parents;
	for (SceneNode node : mNodes) {
		parents.insert(node.mParent);
	}
	return parents;
}

std::vector<size_t> SceneConfig::collectChildNodes(size_t parent)
{
	std::vector<size_t> childNodes;
	for (size_t current = 0; current < mNodes.size(); ++current) {
		if (mNodes[current].mParent == parent) {
			childNodes.push_back(current);
		}
	}
	return childNodes;
}

void SceneConfig::swapNodes(size_t node, size_t otherNode)
{

}

size_t SceneConfig::createSceneNode(const std::string& name)
{
	mNodes.push_back(SceneNode(name));
	return mNodes.size() - 1;
}

} // namespace Forge
