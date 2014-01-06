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

#include "../DynamicLoader.hpp"
#include "Platform/FileSystem/Directory.hpp"
#include <dlfcn.h>
#include <iostream>


namespace Forge {

DynamicLibrary* DynamicLoader::open(std::string const& name)
{
  std::string filename = mSearchPath;
  filename.push_back(FileSystem::Directory::SEPARATOR);
  filename.append(createPlatformName(name));
  LibraryHandle handle = dlopen(filename.c_str(), RTLD_NOW);
  return new DynamicLibrary(handle);
}

std::string DynamicLoader::createPlatformName(std::string const& library)
{
  std::string result("lib");
  result.append(library);
  result.append(".so");
  return result;
}

}
