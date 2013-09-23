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

#pragma once

#include "Graphics/Material/Technique/Technique.h"
#include "Lua/Loader.hpp"
#include <memory>
#include <string>


namespace Forge {

/* A material to be used for a mesh
 *
 * Material contains a technique and metadata about the technique.
 * Material is also responsible for parsing the material file. */

class Material
{
public:
  void loadMaterial(const std::string& materialFile);

  void beginMaterial() const;
  void setTransforms(const glm::mat4& world, const glm::mat4& view, const glm::mat4& projection) const;

  void setDynamicProperty(const std::string& propertyName, const Property& value);
private:
  TechniquePtr mTechnique;
  std::string mMaterialFile;

  friend class Lua::Loader<Material>;
  friend struct std::hash<Material>;
  friend bool operator ==(const Material&, const Material&);
};

bool operator==(const Material& lhs, const Material& rhs);

typedef std::shared_ptr<Material> MaterialPtr;

} // namespace Forge

namespace std {

template<>
struct hash<Forge::Material> {
public:
  size_t operator()(const Forge::Material &m) const
  {
    return std::hash<std::string>()(m.mMaterialFile);
  }
};

}
