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

#include "AssetTraits.hpp"
#include "../Platform/FileSystem/Directory.hpp"
#include "../Util/Log.h"
#include "../Util/Singleton.hpp"
#include <memory>
#include <unordered_map>
#include <unordered_set>


namespace Forge {



/* Generic asset library
 *
 * Add a set of directories and search them for assets of a specific type.
 */
template <class AssetType, bool RefCounted = true>
class AssetLibrary : public Singleton<AssetLibrary<AssetType, RefCounted> >
{
  public:
    AssetLibrary(AssetLibrary&&) = delete;
    AssetLibrary const& operator=(AssetLibrary const&) = delete;

    ~AssetLibrary()
    {
      mAssetInfoMap.clear();
    }

    struct AssetInfo
    {
        std::string filename;
        unsigned int useCount;
        bool valid;
        std::shared_ptr<AssetType> asset;
    };

    void addDirectory(std::string const& dir)
    {
      mAssetDirectories.insert(dir);
    }

    void removeDirectory(std::string const& dir)
    {
      mAssetDirectories.erase(dir);
    }

    void loadAssetInfo()
    {
      for (std::string const& directory : mAssetDirectories)
      {
        parseDirContents(directory);
      }
    }

    AssetInfo const& getAssetInfo(std::string const& assetName) const
    {
      return mAssetInfoMap.at(assetName);
    }

    std::shared_ptr<AssetType> obtainAsset(std::string const& assetName)
    {
      AssetInfo& info = mAssetInfoMap[assetName];

      if (!RefCounted)
      {
        return loadAsset(info.filename);
      }
      else if (!info.valid)
      {
        info.asset = loadAsset(info.filename);
        info.valid = info.asset ? true : false;
        info.useCount = info.valid  ? 1 : 0;
      }
      else if (RefCounted)
      {
        ++info.useCount;
      }

      return info.asset;
    }

    void releaseAsset(std::string const& assetName)
    {
      AssetInfo& info = mAssetInfoMap[assetName];

      if (info.valid && info.useCount > 0)
      {
        --info.useCount;
        if (info.useCount == 0)
        {
          info.valid = false;
          info.asset.reset();
        }
      }
    }

  private:
    AssetLibrary():
       mSupportedExtensions(AssetTraits<AssetType>::fileExtensions)
    {
    }

    /* Loading */
    std::unordered_set<std::string> mAssetDirectories;
    std::string const mSupportedExtensions;

    /* Loads an asset using a method defined via template specialization */
    std::shared_ptr<AssetType> loadAsset(std::string const& filename);

    void parseDirContents(std::string const& directory)
    {
      Log::info << "Looking for " << AssetTraits<AssetType>::assetTypeStr << " assets...\n";
      FileSystem::Directory assetDir(directory);
      for (std::string const& filename : assetDir.listFiles())
      {
        std::string::size_type extensionStart = filename.find_last_of(".");
        bool const noExtension = (extensionStart == std::string::npos);
        std::string extension = noExtension ? "" : filename.substr(extensionStart);
        if (mSupportedExtensions == "" || mSupportedExtensions.find(extension) != std::string::npos)
        {
          AssetInfo info =
          {
            filename,
            0,
            false,
            nullptr
          };
          std::string::size_type nameStart = filename.find_last_of('/')+1;
          std::string assetName =
            filename.substr(
              nameStart,
              extensionStart > nameStart ? extensionStart - nameStart : std::string::npos
            );
          Forge::Log::info << "Added " << AssetTraits<AssetType>::assetTypeStr << " '" << assetName << "'.\n";
          mAssetInfoMap[assetName] = info;
        }
      }
    }

    /* Access */
    std::unordered_map<std::string, AssetInfo> mAssetInfoMap;

    friend class Singleton<AssetLibrary<AssetType, RefCounted> >;
};

}
