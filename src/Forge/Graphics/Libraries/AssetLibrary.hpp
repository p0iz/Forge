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

#include "AssetLoader.hpp"
#include "AssetTraits.hpp"
#include "../../Platform/FileSystem/Directory.hpp"
#include "../../Util/Log.h"
#include "../../Util/Singleton.hpp"
#include <memory>
#include <unordered_map>
#include <unordered_set>


namespace Forge {



/* Generic asset library
 *
 * Add a set of directories and provide a loader for searching them
 * for assets of a specific type.
 */
template <class AssetType, class AssetLoader>
class AssetLibrary : public Singleton<AssetLibrary<AssetType, AssetLoader> >
{
  public:
    AssetLibrary():
       mSupportedExtensions(AssetTraits<AssetType>::fileExtensions)
    {
    }

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

      if (!info.valid)
      {
        info.asset = AssetLoader::loadAsset(info.filename);
        info.valid = info.asset ? true : false;
        info.useCount = info.valid ? 1 : 0;
      }
      else
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
    /* Loading */
    std::unordered_set<std::string> mAssetDirectories;
    std::string const mSupportedExtensions;

    void parseDirContents(std::string const& directory)
    {
      FileSystem::Directory assetDir(directory);
      for (std::string const& filename : assetDir.listFiles())
      {
        std::string::size_type extensionStart = filename.find_last_of(".");
        std::string extension = filename.substr(extensionStart);
        if (mSupportedExtensions.find(extension) != std::string::npos)
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
          Forge::Log::info << "Added asset '" << assetName << "'.\n";
          mAssetInfoMap[assetName] = info;
        }
      }
    }

    /* Access */
    std::unordered_map<std::string, AssetInfo> mAssetInfoMap;
};

}
