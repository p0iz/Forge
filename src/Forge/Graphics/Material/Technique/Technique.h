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

#include "Property.h"

#include "LuaProperties.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Forge {

/* Technique is comprised of one or several shader passes and accompanying properties */
class Technique
{
public:
	explicit Technique(const std::string& name) : mName(name) { }

	// Needed for technique library
	virtual Technique* clone() = 0;

	// Called when starting/stopping application
	virtual void create() = 0;
	virtual void destroy() = 0;

	// Called when starting to draw with the technique
	virtual void beginMaterial() = 0;

	// Called when starting to draw a mesh
	virtual void setTransforms(const glm::mat4& world,
						  const glm::mat4& view,
						  const glm::mat4& projection) = 0;

	// Use integers to speed up comparisons
	const std::string& getName() const {
		return mName;
	}

	virtual void updateProperties(LuaProperties&) = 0;

	void setDynamicProperty(const char* name, Property value) {
		mDynamicProperties[name] = value;
	}

	bool hasDynamicProperty(const char* name) const {
		return mDynamicProperties.count(name) > 0;
	}

	const PropertyValue& getDynamicProperty(const char* name) const {
		return mDynamicProperties.at(name)[0];
	}

private:
	const std::string mName;
	typedef std::unordered_map<std::string, Property> PropertyMap;
	PropertyMap mDynamicProperties;
};

typedef std::shared_ptr<Technique> TechniquePtr;

}
