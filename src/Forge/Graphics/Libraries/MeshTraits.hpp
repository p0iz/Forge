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
#include "../Mesh.h"


namespace Forge {

/* Mesh asset properties */
template <>
struct AssetTraits<Mesh>
{
  typedef Mesh AssetType;
  constexpr static char const* fileExtensions = ".obj";
  constexpr static char const* assetTypeStr = "mesh";
};

typedef AssetTraits<Mesh> MeshTraits;

}
