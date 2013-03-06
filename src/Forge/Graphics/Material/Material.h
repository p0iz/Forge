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

#include "Graphics/Material/Technique/TechniqueLibrary.h"

#include <memory>
#include <string>
#include <vector>

namespace Forge {

class RenderTask;

/* A material to be used for a mesh
 *
 * Material contains a technique and metadata about the technique.
 * Material is also responsible for parsing the material file. */
class Material
{
public:
	void loadMaterial(const char* materialFile, TechniqueLibrary& techLibrary);

	void beginMaterial(const RenderTask& task);
	void beginMesh(const RenderTask& task);

	void setPropertyValue(const char* propertyName, const Property& value);
private:
	TechniquePtr mTechnique;
	std::string mMaterialFile;
};

} // namespace Forge
