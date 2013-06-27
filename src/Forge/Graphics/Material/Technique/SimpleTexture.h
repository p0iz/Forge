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

#include "Graphics/OpenGL/Shader.h"
#include "Graphics/OpenGL/ShaderProgram.h"
#include "Graphics/OpenGL/Texture.hpp"

#include <glm/glm.hpp>

/*
 * IDEA: RenderTask class to encapsulate render state.
 * The RenderTask keeps track of rendering state, e.g.
 * current camera, scene, material and mesh.
 *
 *	- camera (world-to-view-to-projection)
 *
 *	For drawing scene:
 *	- scene ref
 *		For drawing material:
 *		- material ref
 *			For drawing mesh:
 *			- mesh refs (mesh-to-world)
 *			- collect lights closest to mesh and populate light array for forward lighting
 *
 *	Help:
 *  - get matrices
 *	- get scene lighting
 *
 * Workflow:
 *
 *	1. Create render task.
 *	2. Populate render task with render properties (camera, scene)
 *	3. Iterate materials and meshes in scene.
 *	4. Draw scene -> material -> mesh
 */

namespace Forge {

/* Simple texture technique with albedo, gloss and normal mapping */
class SimpleTexture : public Technique
{
public:
	SimpleTexture();

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

	// Textures
	unsigned int mDiffuseMap;
	unsigned int mSpecularMap;
	unsigned int mNormalMap;
	std::vector<unsigned int> mLoadedTextures;

	unsigned int addTexture(const std::string& textureFile);
	void freeTextures();

	// Uniform locations
	int wvpLocation; // World->View->Projection
	int wvLocation; // World->View
	int nLocation; // Normal matrix (upper 3x3 of WorldView)

	int materialAmbientLoc;
	int materialDiffuseLoc;
	int materialSpecularLoc;
	int materialShininessLoc;

	int mDiffuseMapLoc;
	int mSpecularMapLoc;
	int mNormalMapLoc;

};

}
