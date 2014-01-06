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

#include "../DynamicLibrary.hpp"
#include <dlfcn.h>
#include <iostream>


namespace Forge {

DynamicLibrary::DynamicLibrary():
  mHandle(nullptr),
  mSymbolCache()
{
}

void* DynamicLibrary::getSymbol(std::string const& symbol)
{
  void* symbolPtr = dlsym(mHandle, symbol.c_str());
  char const* error = dlerror();
  std::cerr << error << "\n";
  return symbolPtr;
}

void DynamicLibrary::freeHandle()
{
  if (mHandle != nullptr)
  {
    dlclose(mHandle);
    mHandle = nullptr;
  }
}

}
