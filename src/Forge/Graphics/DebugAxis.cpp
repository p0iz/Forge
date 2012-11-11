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

#include "DebugAxis.h"

#include "Shader/Shader.h"
#include "Shader/ShaderProgram.h"

#include <glm/glm.hpp>
#include <iostream>

namespace Forge {

DebugAxis* DebugAxis::singleton = 0;

bool DebugAxis::showDebug = false;

DebugAxis& DebugAxis::getInstance()
{
	if (!singleton)
		singleton = new DebugAxis;
	if (!singleton->initialized)
		singleton->initialize();
	return *singleton;
}

void DebugAxis::draw(const glm::mat4x4& mvpMatrix) const
{
	if (!showDebug)
		return;
	glBindVertexArray(debugVertexArrayId);

	debugShaderProgram.use();

	glUniformMatrix4fv(debugUniformMVP, 1, GL_FALSE, &mvpMatrix[0][0]);

	glDrawArrays(GL_LINES, 0, 6);

	debugShaderProgram.release();

	glBindVertexArray(0);
}

DebugAxis::DebugAxis()
	: initialized(GL_FALSE)
{
}


void DebugAxis::initialize()
{
	initialized = GL_TRUE;

	GLfloat debugVertexData[] =
	{
		0,0,0,
		10,0,0,
		0,0,0,
		0,10,0,
		0,0,0,
		0,0,10
	};

	GLfloat debugVertexColor[] =
	{
		1,0,0,
		1,0,0,
		0,1,0,
		0,1,0,
		0,0,1,
		0,0,1
	};

	// create the debug shader program
	debugVertexShader.create(GL_VERTEX_SHADER);
	debugVertexShader.loadCode("data/shaders/DebugShader.vert");
	debugVertexShader.compile();

	debugFragmentShader.create(GL_FRAGMENT_SHADER);
	debugFragmentShader.loadCode("data/shaders/DebugShader.frag");
	debugFragmentShader.compile();

	debugShaderProgram.create();
	debugShaderProgram.setVertexShader(debugVertexShader.getId());
	debugShaderProgram.setFragmentShader(debugFragmentShader.getId());

	if (debugShaderProgram.link() != GL_TRUE)
	{
		std::cout << "Debug shader failed with the following output:\n"
				  << debugShaderProgram.getProgramInfoLog()
				  << std::flush;
	}

	debugUniformMVP = debugShaderProgram.getUniformLocation("MVP");

	// Get vertex array and buffers
	glGenVertexArrays(1, &debugVertexArrayId);
	glGenBuffers(2, debugBuffers);

	// Bind VAO
	glBindVertexArray(debugVertexArrayId);

	// Fill buffers
	glBindBuffer(GL_ARRAY_BUFFER, debugBuffers[0]);
	glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(debugVertexData),
				debugVertexData,
				GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, debugBuffers[1]);
	glBufferData(
				GL_ARRAY_BUFFER,
				sizeof(debugVertexColor),
				debugVertexColor,
				GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Finished, now unbind
	glBindVertexArray(0);
}

void DebugAxis::toggleDebuggingInfo()
{
	showDebug = !showDebug;
}

void DebugAxis::setDebuggingInfo(bool state)
{
	showDebug = state;
}

DebugAxis::~DebugAxis()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(2, debugBuffers);
	glDeleteVertexArrays(1, &debugVertexArrayId);
}

} // namespace Forge
