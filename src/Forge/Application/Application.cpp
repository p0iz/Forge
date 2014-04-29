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
 * Copyright 2014 Tommi Martela
 *
 */

#include "Application.hpp"
#include "Assets/AssetManager.hpp"
#include "Graphics/RendererThread.hpp"
#include "GameObject/GameObject.hpp"
#include "GameObject/Component/MeshInstance.hpp"
#include "GameObject/Component/Script.hpp"
#include "GameObject/Transformation.hpp"
#include "Util/Internal/Keeper.hpp"


namespace Forge {

Application::Application():
  mRendererThread(nullptr),
  mAssetManager(nullptr),
  mMeshContainer(nullptr),
  mScriptContainer(nullptr),
  mTransformContainer(nullptr),
  mConfigFile("Forge.config")
{
}

Application::~Application()
{
}

bool Application::initialize(const std::string& configFile)
{
  mConfigFile = configFile;

  // Create data storage
  mAssetManager.reset(new AssetManager("./plugins"));
  mGameObjectContainer.reset(new Keeper<GameObject>());
  mMeshContainer.reset(new Keeper<MeshInstance>());
  mScriptContainer.reset(new Keeper<Script>());
  mTransformContainer.reset(new Keeper<Transformation>());

  mRendererThread.reset(new RendererThread(*this));

  return true;
}

void Application::stopRendering()
{
  if (mRendererThread)
  {
    mRendererThread->stop();
  }
}

GraphicsContext* Application::createAuxContext()
{
  return mRendererThread ? mRendererThread->createAuxContext() : nullptr;
}

RendererThread& Application::rendererThread()
{
  return *mRendererThread;
}

Keeper<Light> const& Application::lights() const
{
  return *mLightContainer;
}

Keeper<Light>& Application::lights()
{
  return *mLightContainer;
}

const Keeper<GameObject>&Application::objects() const
{
  return *mGameObjectContainer;
}

Keeper<GameObject>&Application::objects()
{
  return *mGameObjectContainer;
}

Keeper<MeshInstance> const& Application::meshes() const
{
  return *mMeshContainer;
}

Keeper<MeshInstance>& Application::meshes()
{
  return *mMeshContainer;
}

Keeper<Script> const& Application::scripts() const
{
  return *mScriptContainer;
}

Keeper<Script>& Application::scripts()
{
  return *mScriptContainer;
}

const Keeper<Transformation>&Application::transforms() const
{
  return *mTransformContainer;
}

Keeper<Transformation>&Application::transforms()
{
  return *mTransformContainer;
}

AssetHandle Application::loadAsset(const std::string& asset)
{
  return mAssetManager->load(asset);
}

std::shared_ptr<void> Application::getAsset(const AssetHandle& handle)
{
  return mAssetManager->get(handle);
}

}
