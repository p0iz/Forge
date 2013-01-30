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

#include "Util/HashUtils.h"

#include <cassert>
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

namespace Forge {

class RenderTask;
class JsonObject;

/* Technique is comprised of one or several shader passes and accompanying properties */
class Technique
{
public:

	// Only string literals allowed
	template <unsigned int N>
	explicit Technique(const char (&name)[N]) : mName(HashUtils::StringHash(name)), mNameStr(name)
	{
	}

	// Needed for technique library
	virtual Technique* clone() = 0;

	// Called when starting/stopping application
	virtual void create() = 0;
	virtual void destroy() = 0;

	// Called when starting to draw a mesh
	virtual void beginMesh(const RenderTask&) = 0;

	// Use integers to speed up comparisons
	size_t getName() const
	{
		return mName;
	}

	// Use only for debugging
	const char* getNameStr() const
	{
		return mNameStr;
	}

	virtual void updateProperties(const JsonObject&) { }

	void setProperty(size_t name, Property value)
	{
		mProperties[name] = value;
	}

	bool hasProperty(size_t name) const
	{
		return mProperties.count(name) > 0;
	}

	const PropertyValue& getProperty(size_t name) const
	{
		return mProperties.at(name)[0];
	}

private:
	size_t mName;
	const char* mNameStr;
	typedef std::unordered_map<size_t, Property> PropertyMap;
	PropertyMap mProperties;
};

}
