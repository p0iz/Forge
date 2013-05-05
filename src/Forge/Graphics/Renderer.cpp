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

#include "GL/glew.h"

#include "Renderer.h"

#include "DebugAxis.h"
#include "Scene/SceneConfig.hpp"

namespace Forge {

Renderer::~Renderer()
{
	Light::destroyBuffer();
}

void Renderer::initialize()
{
	// Flag to load all extensions, needed by OpenGL 3.3
	glewExperimental = GL_TRUE;
	assert(glewInit() == GLEW_OK);

	glClearColor(0.6f,0.5f,0.7f,1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	DebugAxis::getSingleton();
	Light::createBuffer();
}

void Renderer::updateViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void Renderer::updateLightData(const SceneConfig& scene, const glm::mat4& view)
{
	for (const Light& light : scene.lights) {
		if (light.id >= 0) {
			Light::Data& lightData = Light::data[light.id];
			lightData.viewSpacePosition = view * light.position;
		}
	}
	Light::updateBuffer();
}

void Renderer::render(const SceneConfig& scene)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	const glm::mat4 view = scene.getCamera().getViewMatrix();
	const glm::mat4 projection = scene.getCamera().getProjectionMatrix();

	// Update view space light positions
	updateLightData(scene, view);

	// Render attached meshes
	for (auto materialMeshPair : scene.mMaterialMeshMap) {
		const Material& material = materialMeshPair.first;
		bool materialSelected = false;
		const std::vector<MeshPtr>& meshes = materialMeshPair.second;
		for (MeshPtr mesh : meshes) {
			// For each mesh, get the world transform
			for (size_t nodeId : mesh->getAttachedNodes()) {
				if (!materialSelected) {
					material.beginMaterial();
					materialSelected = true;
				}
				const glm::mat4& world = scene.getSceneNode(nodeId).mWorldTransform.getMatrix();
				material.setTransforms(world, view, projection);
				mesh->draw();
			}
		}
	}

	// Render debug overlay
	if (DebugAxis::isDebugVisible()) {
		//DebugAxis::getSingleton().render(scene);
	}
	// Post process
}

void Renderer::renderDebugOverlay(const SceneConfig& scene) {

}

}
