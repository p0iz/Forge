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
#include "Graphics/Loaders/ImageLoader.h"
#include "Technique/TechniqueLibrary.h"
#include "Util/Log.h"

#include <GL/glew.h>

namespace Forge {

void Material::loadMaterial(const std::string& materialFile, TechniqueLibrary& techLibrary)
{
	mMaterialFile = materialFile;
	// First destroy old technique to make room for new
	if (mTechnique) {
		mTechnique->destroy();
	}

	MaterialLoader loader;
	loader.setTargetMaterial(this);
	loader.setTechniqueLibrary(techLibrary);
	loader.loadFile(materialFile);
}

void Material::beginMaterial() const
{
	mTechnique->beginMaterial();
}

void Material::setTransforms(const glm::mat4& world,
							 const glm::mat4& view,
							 const glm::mat4& projection) const
{
	mTechnique->setTransforms(world, view, projection);
}

void Material::setDynamicProperty(const std::string& propertyName, const Property& value)
{
	mTechnique->setDynamicProperty(propertyName.c_str(), value);
}

bool operator==(const Material& lhs, const Material& rhs)
{
	return lhs.mMaterialFile == rhs.mMaterialFile;
}

} // namespace Forge
