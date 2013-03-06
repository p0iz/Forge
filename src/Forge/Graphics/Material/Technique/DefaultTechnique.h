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

namespace Forge {

/* Default technique that just renders and ugly pink */
class DefaultTechnique : public Technique
{
public:
	DefaultTechnique();
	virtual Technique* clone();
	virtual void create();
	virtual void destroy();
	virtual void updateProperties(const JsonObject &);
	virtual void beginMaterial(const RenderTask& task);
	virtual void beginMesh(const RenderTask& task);
private:
	Shader vertexShader;
	Shader fragmentShader;
	ShaderProgram shaderProgram;

	// Uniform location
	unsigned int wvpLocation;
};

}
