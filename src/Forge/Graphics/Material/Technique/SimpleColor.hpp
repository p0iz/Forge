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

#include "Technique.h"

#include "../../Shader/Shader.h"
#include "../../Shader/ShaderProgram.h"

#include <glm/glm.hpp>

namespace Forge {

/* Simple color technique without texturing */
class SimpleColor : public Technique
{
public:
	SimpleColor();

	virtual Technique* clone();

	virtual void create();
	virtual void destroy();

	virtual void updateProperties(LuaProperties& properties);

	virtual void beginMaterial();
	virtual void setTransforms(const glm::mat4& world,
						  const glm::mat4& view,
						  const glm::mat4& projection);

private:
	Shader vertexShader;
	Shader fragmentShader;
	ShaderProgram shaderProgram;

	// Lighting
	unsigned int lightsUniformIndex;

	// Uniform locations
	int wvpLocation; // World->View->Projection
	int wvLocation; // World->View
	int nLocation; // Normal matrix (upper 3x3 of WorldView)

	int materialAmbientLoc;
	int materialDiffuseLoc;
	int materialSpecularLoc;
	int materialShininessLoc;

};

}
