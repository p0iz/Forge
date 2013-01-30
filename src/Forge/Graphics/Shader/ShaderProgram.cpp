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

#include "ShaderProgram.h"

#include <GL/glew.h>

#include <vector>

namespace Forge {

ShaderProgram::ShaderProgram()
	: mId(0), mVertexShaderId(0), mFragmentShaderId(0)
{
}

ShaderProgram::~ShaderProgram()
{
	int numShaders = 0;
	glGetProgramiv(mId, GL_ATTACHED_SHADERS, &numShaders);

	std::vector<unsigned int> shaders(numShaders);
	glGetAttachedShaders(mId, numShaders, nullptr, &shaders[0]);
	for (unsigned int shader : shaders)
	{
		glDetachShader(mId, shader);
	}
	glDeleteProgram(mId);
}

void ShaderProgram::create()
{
	mId = glCreateProgram();
}

const int ShaderProgram::link()
{
	if (!mId)
		mId = glCreateProgram();

	glLinkProgram(mId);
	GLint linkStatus;
	glGetProgramiv(mId, GL_LINK_STATUS, &linkStatus);
	return linkStatus;
}



const GLuint ShaderProgram::getAttribLocation(const char *attribName) const
{
	return glGetAttribLocation(mId, attribName);
}

const GLuint ShaderProgram::getUniformLocation(const char *uniformName) const
{
	return glGetUniformLocation(mId, uniformName);
}

const unsigned int ShaderProgram::getId()
{
	return mId;
}

const std::string ShaderProgram::getProgramInfoLog() const
{
	std::string logString;
	int logLength = 0;
	glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &logLength);
	char* logChars = new char[logLength];
	glGetProgramInfoLog(mId, logLength, nullptr, logChars);
	logString.assign(logChars);
	delete[] logChars;
	return logString;
}

void ShaderProgram::setVertexShader(unsigned int shader)
{
	mVertexShaderId = shader;
	glAttachShader(mId, shader);
}

void ShaderProgram::setGeometryShader(unsigned int shader)
{
	mVertexShaderId = shader;
	glAttachShader(mId, shader);
}

void ShaderProgram::setFragmentShader(unsigned int shader)
{
	mFragmentShaderId = shader;
	glAttachShader(mId, shader);
}

void ShaderProgram::use() const
{
	glUseProgram(mId);
}

void ShaderProgram::release()
{
	glUseProgram(0);
}

} // namespace Forge
