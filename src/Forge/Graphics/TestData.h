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

#ifndef TESTDATA_H
#define TESTDATA_H

#include "Mesh.h"
#include "Material/Material.h"
#include "Material/Technique/TechniqueLibrary.h"
#include "Light/Light.hpp"
#include "Text/Text.hpp"
#include "Transformation.hpp"

#include <memory>

#define NUMBER_OF_CUBES 10
#define CIRCLE_WIDTH 10

namespace Forge {

class RenderTask;

class TestData
{
public:
	void draw(RenderTask& task);
	void create();
	void destroy();

	void updateText(int w, int h);

	void setTestUniforms(const glm::mat4x4& viewMatrix);

	void reloadTestMaterial();

private:
	Material cubeMaterial;
	Material lampMaterial;
	Material roomMaterial;

	TechniqueLibrary mTechniqueLibrary;

	std::shared_ptr<Mesh> roomMesh;
	std::shared_ptr<Mesh> cubeMesh;
	std::shared_ptr<Mesh> lampMesh;
	Transformation cubeTransforms[NUMBER_OF_CUBES];
	Transformation roomTransform;

	Text mLightText;
	Text mViewText;

	Light mTestLights[Light::MAX_LIGHTS];
};

} // namespace Forge

#endif // TESTDATA_H
