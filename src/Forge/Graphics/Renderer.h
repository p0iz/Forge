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

#include <glm/glm.hpp>

namespace Forge {

class SceneConfig;

/* A class that is used to render scenes from scene configurations */
class Renderer
{
public:
	~Renderer();
	void initialize();
	void updateViewport(int width, int height);
	void render(const SceneConfig& scene);
private:
	void renderDebugOverlay(const SceneConfig& scene);
	void updateLightData(const SceneConfig& scene, const glm::mat4& view);
};

}