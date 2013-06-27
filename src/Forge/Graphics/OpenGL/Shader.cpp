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

#include "Shader.h"

#include <GL/glew.h>

#include <cassert>
#include <fstream>
#include <sstream>

namespace Forge {

Shader::Shader()
	: mId(0), mType(0)
{
}

Shader::~Shader()
{
	if (mId)
	{
		glDeleteShader(mId);
	}
}

void Shader::create(Type type)
{
	if (mId)
	{
		glDeleteShader(mId);
	}

    switch (type)
    {
	case Type::VERTEX_SHADER:
		mType = GL_VERTEX_SHADER;
        mId = glCreateShader(GL_VERTEX_SHADER);
        break;
	case Type::FRAGMENT_SHADER:
		mType = GL_FRAGMENT_SHADER;
        mId = glCreateShader(GL_FRAGMENT_SHADER);
        break;
	case Type::GEOMETRY_SHADER:
		mType = GL_GEOMETRY_SHADER;
        mId = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    }
}

const GLint Shader::compile()
{
	glCompileShader(mId);
	GLint result = GL_FALSE;
	glGetShaderiv(mId, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		printInfoLog();
	}
	return result;
}

std::string Shader::getInfoLog() const
{
	std::string infoLog;
	int logLength;
	glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &logLength);
	char* shaderInfoLog = new char[logLength];
	glGetShaderInfoLog(mId, logLength, NULL, shaderInfoLog);
	infoLog.assign(shaderInfoLog);
	delete[] shaderInfoLog;
	return infoLog;
}

void Shader::printInfoLog() const
{
	std::string infoLog = getInfoLog();

	const char* shaderType = nullptr;
	switch (mType)
	{
	case Type::FRAGMENT_SHADER:
		shaderType = "fragment";
		break;
	case Type::VERTEX_SHADER:
		shaderType = "vertex";
		break;
	case Type::GEOMETRY_SHADER:
		shaderType = "geometry";
		break;
    default:
        shaderType = "unsupported";
        break;
	}

	printf("Error while compiling %s shader: %s\n",
		   shaderType,
		   infoLog.c_str());
}

void Shader::loadCode(const std::string& file)
{
	std::ifstream shaderFile(file);
	if (shaderFile)
	{
		std::stringstream shaderBuffer;
		shaderBuffer << shaderFile.rdbuf();
		std::string shaderCode(shaderBuffer.str());
		const char* code = shaderCode.c_str();
		int codeLength = static_cast<int>(shaderCode.length());
		glShaderSource(mId, 1, &code, &codeLength);
	}
}

} // namespace Forge
