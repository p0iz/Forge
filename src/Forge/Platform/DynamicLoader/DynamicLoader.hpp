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

#include "DynamicLibrary.hpp"
#include "ForgeExport.h"
#include <iosfwd>
#include <unordered_map>


#ifdef _WIN32
  #include "windows.h"
  typedef HMODULE LibraryHandle;
#else
  typedef void* LibraryHandle;
#endif


namespace Forge {

class DynamicLoader
{
  public:
    explicit DynamicLoader(std::string const& searchPath);

    bool isLoaded() const;

    DynamicLibrary* open(std::string const& name);

  private:
    std::string mSearchPath;

    static std::string createPlatformName(std::string const& library);

};

}
