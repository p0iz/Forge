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

#pragma once

#include "ForgeExport.h"
#include "Assets/AssetHandle.hpp"
#include <memory>
#include <string>


namespace Forge {

class AssetManager;
class GraphicsContext;
class RendererThread;

// Data storage forward declarations
template <class ItemType>
class Keeper;
class GameObject;
class Light;
class MeshInstance;
class Script;
class Transformation;

// Central hub for a Forge application
class FORGE_EXPORT Application
{
  public:
    Application();
    ~Application();

    bool initialize(std::string const& configFile = "Forge.config");

    void stopRendering();

    GraphicsContext* createAuxContext();

    RendererThread& rendererThread();

    Keeper<Light> const& lights() const;
    Keeper<Light>& lights();
    Keeper<GameObject> const& objects() const;
    Keeper<GameObject>& objects();
    Keeper<MeshInstance> const& meshes() const;
    Keeper<MeshInstance>& meshes();
    Keeper<Script> const& scripts() const;
    Keeper<Script>& scripts();
    Keeper<Transformation> const& transforms() const;
    Keeper<Transformation>& transforms();

    AssetHandle loadAsset(std::string const& asset);
    std::shared_ptr<void> getAsset(AssetHandle const&);
  private:
    // Visualization
    std::shared_ptr<RendererThread> mRendererThread;

    // Data
    std::shared_ptr<AssetManager> mAssetManager;
    std::shared_ptr<Keeper<GameObject>> mGameObjectContainer;
    std::shared_ptr<Keeper<Light>> mLightContainer;
    std::shared_ptr<Keeper<MeshInstance>> mMeshContainer;
    std::shared_ptr<Keeper<Script>> mScriptContainer;
    std::shared_ptr<Keeper<Transformation>> mTransformContainer;

    // Configuration
    std::string mConfigFile;
};

}
