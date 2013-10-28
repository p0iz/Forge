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

#include "Material.h"
#include "MaterialLoader.hpp"
#include "Graphics/Libraries/TextureLibrary.hpp"
#include "Graphics/Libraries/TechniqueLibrary.hpp"
#include "Util/Log.h"

#include <GL/glew.h>

namespace Forge {

Material::~Material()
{
  clearUsers();
  Graphics::TechniqueLibrary::instance().releaseAsset(mTechnique->getName());
}

void Material::loadMaterial(const std::string& materialFile)
{
  mMaterialFile = materialFile;
  // First destroy old technique to make room for new
  if (mTechnique) {
    Graphics::TechniqueLibrary::instance().releaseAsset(mTechnique->getName());
  }

  MaterialLoader loader;
  loader.setTarget(*this);
  loader.loadFile(materialFile);
}

void Material::beginMaterial() const
{
  mTechnique->beginMaterial();
}

void Material::setTransforms(
    glm::mat4 const& world,
    glm::mat4 const& view,
    glm::mat4 const& projection
  ) const
{
  mTechnique->setTransforms(world, view, projection);
}

const std::vector<MeshPtr>&Material::getMeshes() const
{
  return mMeshes;
}

void Material::useOn(MeshPtr const& mesh)
{
  mMeshes.push_back(mesh);
}

void Material::clearUsers()
{
  mMeshes.clear();
}

bool operator==(const Material& lhs, const Material& rhs)
{
  return lhs.mMaterialFile == rhs.mMaterialFile;
}

} // namespace Forge
