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

#include "Graphics/Material/Technique/DefaultTechnique.h"
#include "Graphics/Material/Technique/TechniqueLibrary.h"
#include "Util/HashUtils.h"
#include "Util/Log.h"

namespace Forge {

TechniqueLibrary::~TechniqueLibrary()
{
	for (auto techniquePair : mTechniqueMap)
	{
		techniquePair.second->destroy();
	}
}

void TechniqueLibrary::add(Technique* technique)
{
	std::shared_ptr<Technique> techPtr(technique);
	mTechniqueMap[technique->getName()] = techPtr;
	Log::info << "Added technique '" << technique->getNameStr()
			  << "' (hash: " << technique->getName() << ") to library.\n";
}

TechniquePtr TechniqueLibrary::get(size_t techniqueName) const
{
	TechniquePtr technique(new DefaultTechnique);

	if (mTechniqueMap.count(techniqueName) > 0)
		technique.reset(mTechniqueMap.at(techniqueName)->clone());
	else
	{
		Log::error << "Could not find technique '" << techniqueName << "' in technique library!\n";
	}

	return technique;
}

}
