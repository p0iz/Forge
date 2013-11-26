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
#include "../Libraries/MaterialLibrary.hpp"
#include "../Libraries/MeshLibrary.hpp"
#include "../TargetCamera.h"
#include "Util/Exceptions.hpp"
#include "Util/Log.h"

#include <algorithm>
#include <string>

namespace Forge {

SceneConfig::SceneConfig():
  mNodes(1, SceneNode("Root Node")),
  mRootNode(mNodes[0]),
  mUsedMeshes()
{
}

SceneConfig::~SceneConfig()
{
  clearScene();
}

void SceneConfig::clearScene()
{
  // Release assets
  for (std::string const& material : mUsedMaterials)
  {
    Graphics::MaterialLibrary::instance().releaseAsset(material);
  }
  for (std::string const& mesh : mUsedMeshes)
  {
    Graphics::MeshLibrary::instance().releaseAsset(mesh);
  }
  for (Light& light : lights)
  {
    light.releaseDataIndex();
  }

  mNodes.clear();

  mCurrentCamera = nullptr;
}

void SceneConfig::removeSceneNode(SceneNodeId id)
{
  auto iterator = mNodes.begin()+id;
  mNodes.erase(iterator);
  for (SceneNodeId current = id; current < mNodes.size(); ++current) {
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

SceneNode& SceneConfig::getSceneNode(SceneNodeId id) {
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

const SceneNode& SceneConfig::getSceneNode(SceneNodeId id) const {
  return mNodes[id];
}

const Camera& SceneConfig::getCamera() const
{
  return *mCurrentCamera;
}

void SceneConfig::setCamera(Camera& camera)
{
  mCurrentCamera = &camera;
}

void SceneConfig::validateSceneGraph()
{
  // Collect all parent nodes
  std::unordered_set<SceneNodeId> parents = collectParents();

  // For each parent node, verify that all children are after it in the vector
  for (SceneNodeId parent : parents) {
    std::vector<SceneNodeId> childNodes = collectChildNodes(parent);
    SceneNodeId newParentPosition = parent;

    for (SceneNodeId node : childNodes) {
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

void SceneConfig::addUsedMesh(std::string const& meshName)
{
  mUsedMeshes.push_back(meshName);
}

void SceneConfig::addUsedMaterial(std::string const& materialName)
{
  mUsedMaterials.push_back(materialName);
}

std::vector<std::string> const& SceneConfig::getUsedMaterials() const
{
  return mUsedMaterials;
}

void SceneConfig::updateNodeParents(SceneNodeId newParent, SceneNodeId oldParent) {
  for (SceneNode& node : mNodes) {
    if (node.mParent == oldParent) {
      node.mParent = newParent;
    }
  }
}

std::unordered_set<SceneNodeId> SceneConfig::collectParents()
{
  std::unordered_set<SceneNodeId> parents;
  for (SceneNode node : mNodes) {
    parents.insert(node.mParent);
  }
  return parents;
}

std::vector<SceneNodeId> SceneConfig::collectChildNodes(SceneNodeId parent)
{
  std::vector<SceneNodeId> childNodes;
  for (SceneNodeId current = 0; current < mNodes.size(); ++current) {
    if (mNodes[current].mParent == parent) {
      childNodes.push_back(current);
    }
  }
  return childNodes;
}

void SceneConfig::swapNodes(SceneNodeId node, SceneNodeId otherNode)
{

}

SceneNodeId SceneConfig::createSceneNode(const std::string& name)
{
  mNodes.push_back(SceneNode(name));
  SceneNodeId id = mNodes.size() - 1;
  mNodes[id].mId = id;
  return id;
}

} // namespace Forge
