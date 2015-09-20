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

#include "Lua/UserdataMap.hpp"
#include "Graphics/Light/Light.hpp"
#include "Material/Technique/Technique.hpp"
#include <glm/glm.hpp>
#include "Platform/Window/RenderWindow.hpp"


namespace Forge {
class Camera;
class SceneConfig;
}

namespace Forge {

class Viewport;

/* A class that is used to render scenes from scene configurations */
class Renderer
{
public:
  Renderer();
  ~Renderer();

  void initialize();
  void deinitialize();

  void updateViewport(int width, int height);

  void frameUpdate();

  RenderWindow const& window();

  void addViewport(std::string const& name, Viewport* viewport);

  Viewport* getViewport(std::string const& name);

  void setMeshAssets(UserdataMap* meshmap);

  void setLights(std::vector<Light>* lights);

private:
  bool mInitialized;
  void updateLightData(std::vector<Light> const& lights, const glm::mat4& view);
  RenderWindow mWindow;
  UserdataMap* mMeshes;
  std::vector<Light>* mLights;
  std::unordered_map<std::string, Viewport*> mViewports;

  void render(Viewport const& viewport, UserdataMap* meshes, std::vector<Light> const& lights);

  Technique* mTechnique;
};

}
