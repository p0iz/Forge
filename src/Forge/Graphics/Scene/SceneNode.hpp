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

#include "Graphics/Mesh.h"
#include "Graphics/Scene/Transformation.hpp"

#include <string>
#include <set>

namespace Forge {

class SceneConfig;

/* Scene node implementation
 *
 *	How to setup:
 *
 *	1. Create a scene config
 *	2. Create scene nodes from scene config
 *	3. Arrange nodes into parents/children
 *
 */

struct SceneNode {
	SceneNode(const std::string& name, size_t parent = 0);
	std::string mName;
	size_t mParent;
	Transformation mWorldTransform;
};

}