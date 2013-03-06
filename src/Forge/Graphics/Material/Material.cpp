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
#include "Graphics/Loaders/ImageLoader.h"
#include "Technique/Technique.h"
#include "Util/HashUtils.h"
#include "Util/JsonParser.h"
#include "Util/Log.h"

#include <algorithm>
#include <cassert>
#include <GL/glew.h>

namespace Forge {

void Material::loadMaterial(const char* material_file, TechniqueLibrary &techLibrary)
{
	// Parse material file
	JsonParser matParser(material_file);
	assert(matParser.parse());
	JsonObject parsed_data = matParser.getRootObject();
	std::shared_ptr<JsonObject> properties = parsed_data.key_values["Properties"].object;

	// Load and setup technique
	if (mTechnique) {
		mTechnique->destroy();
	}
	std::string techniqueName = parsed_data.key_values["Technique"].value[0];
	mTechnique = techLibrary.get(HashUtils::StringHash(techniqueName));
	mTechnique->create();
	if (properties) {
		mTechnique->updateProperties(*properties);
	}
}

void Material::beginMaterial(const RenderTask& task)
{
	mTechnique->beginMaterial(task);
}

void Material::beginMesh(const RenderTask& task)
{
	mTechnique->beginMesh(task);
}

void Material::setPropertyValue(const char* propertyName, const Property& value)
{
	mTechnique->setProperty(HashUtils::StringHash(propertyName), value);
}

} // namespace Forge
