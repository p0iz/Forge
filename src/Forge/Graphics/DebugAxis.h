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

#ifndef DEBUGDRAWABLE_H
#define DEBUGDRAWABLE_H

#include "OpenGL/Shader.h"
#include "OpenGL/ShaderProgram.h"

#include "Util/Singleton.hpp"

#include <glm/glm.hpp>

namespace Forge {

class SceneConfig;

class DebugAxis : public Singleton<DebugAxis>
{
public:
	DebugAxis();
	~DebugAxis();

	static void toggleDebuggingInfo();
	static void setDebuggingInfo(bool state);
	static bool isDebugVisible();

	void render(const SceneConfig& scene) const;

private:
	void initialize();

	unsigned int debugVertexArrayId;
	unsigned int debugBuffers[2];
	unsigned int debugUniformMVP;

	Shader debugVertexShader;
	Shader debugFragmentShader;
	ShaderProgram debugShaderProgram;

	int initialized;

	static DebugAxis* singleton;
	static bool showDebug;
};

} // namespace Forge

#endif // DEBUGDRAWABLE_H
