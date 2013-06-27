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

#include "Util/Log.h"

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

bool ShaderProgram::link()
{
	if (!mId)
		mId = glCreateProgram();

	glLinkProgram(mId);
	GLint linkStatus;
	glGetProgramiv(mId, GL_LINK_STATUS, &linkStatus);
    return linkStatus == GL_TRUE;
}


void ShaderProgram::setUniform(const unsigned int location,
							   const unsigned int count,
							   const unsigned int elements,
							   const float* data)
{
	switch(elements)
	{
	case 1:
		glUniform1fv(location, count, data);
	case 2:
		glUniform2fv(location, count, data);
	case 3:
		glUniform3fv(location, count, data);
	case 4:
		glUniform4fv(location, count, data);
	default:
		Log::error << __FILE__" " << __LINE__ << ": Unsupported amount of elements in uniform data!\n";
	}
}

void ShaderProgram::setUniform(const unsigned int location,
							   const unsigned int count,
							   const unsigned int elements,
							   const int* data)
{
	switch(elements)
	{
	case 1:
		glUniform1iv(location, count, data);
	case 2:
		glUniform2iv(location, count, data);
	case 3:
		glUniform3iv(location, count, data);
	case 4:
		glUniform4iv(location, count, data);
	default:
		Log::error << __FILE__" " << __LINE__ << ": Unsupported amount of elements in uniform data!\n";
	}
}

void ShaderProgram::setUniform(const unsigned int location,
							   const unsigned int count,
							   const unsigned int elements,
							   const unsigned int* data)
{
	switch(elements)
	{
	case 1:
		glUniform1uiv(location, count, data);
		break;
	case 2:
		glUniform2uiv(location, count, data);
		break;
	case 3:
		glUniform3uiv(location, count, data);
		break;
	case 4:
		glUniform4uiv(location, count, data);
		break;
	default:
		Log::error << __FILE__" " << __LINE__ << ": Unsupported amount of elements in uniform data!\n";
	}
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

void ShaderProgram::setUniformMatrix3fv(const unsigned int location,
										const unsigned int count,
										const bool transposed,
										const float *data)
{
	glUniformMatrix3fv(location, count, transposed ? GL_TRUE : GL_FALSE, data);
}

void ShaderProgram::setUniformMatrix4fv(const unsigned int location,
										const unsigned int count,
										const bool transposed,
										const float *data)
{
	glUniformMatrix4fv(location, count, transposed ? GL_TRUE : GL_FALSE, data);
}

void ShaderProgram::bindUniform(const char* uniformName, unsigned int bindingPoint)
{
	unsigned int uniformBlockIndex = glGetUniformBlockIndex(mId, uniformName);
	glUniformBlockBinding(mId, uniformBlockIndex, bindingPoint);
}

} // namespace Forge
