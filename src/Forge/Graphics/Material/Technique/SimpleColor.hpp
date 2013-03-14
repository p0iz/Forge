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

#include "../../Light/Light.hpp"
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

	void updateLights(const Light lights[]);

	virtual void updateProperties(LuaProperties& properties);

	virtual void beginMaterial(const RenderTask& task);
	virtual void beginMesh(const RenderTask& task);
private:
	Shader vertexShader;
	Shader fragmentShader;
	ShaderProgram shaderProgram;

	// Lighting
	const int lightBindingPoint = 1;
	unsigned int lightsUniformIndex;
	unsigned int lightBuffer;

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
