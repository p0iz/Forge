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

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace Forge {

enum UniformType
{
	REGULAR,
	WVP_MATRIX,
	WV_MATRIX,
	NORMAL_MATRIX
};

struct Uniform
{
	virtual void applyData() const = 0;
	std::string mName;
	unsigned int mLocation;
};

template <class DataType>
struct DataUniform : public Uniform
{
	virtual void applyData() const;
	std::vector<DataType> mData;
};

template <>
void DataUniform<float>::applyData() const
{
	glUniform1fv(mLocation, mData.size(), &mData[0]);
}

template<>
void DataUniform<int>::applyData() const
{
	glUniform1iv(mLocation, mData.size(), &mData[0]);
}

template<>
void DataUniform<unsigned int>::applyData() const
{
	glUniform1uiv(mLocation, mData.size(), &mData[0]);
}

template <>
void DataUniform<glm::ivec2>::applyData() const
{
	glUniform2iv(mLocation, mData.size(), &mData[0][0]);
}

template <>
void DataUniform<glm::ivec3>::applyData() const
{
	glUniform3iv(mLocation, mData.size(), &mData[0][0]);
}

template <>
void DataUniform<glm::ivec4>::applyData() const
{
	glUniform4iv(mLocation, mData.size(), &mData[0][0]);
}

template <>
void DataUniform<glm::uvec2>::applyData() const
{
	glUniform2uiv(mLocation, mData.size(), &mData[0][0]);
}

template <>
void DataUniform<glm::uvec3>::applyData() const
{
	glUniform3uiv(mLocation, mData.size(), &mData[0][0]);
}

template <>
void DataUniform<glm::uvec4>::applyData() const
{
	glUniform4uiv(mLocation, mData.size(), &mData[0][0]);
}

template <>
void DataUniform<glm::vec2>::applyData() const
{
	glUniform2fv(mLocation, mData.size(), &mData[0][0]);
}

template <>
void DataUniform<glm::vec3>::applyData() const
{
	glUniform3fv(mLocation, mData.size(), &mData[0][0]);
}

template <>
void DataUniform<glm::vec4>::applyData() const
{
	glUniform4fv(mLocation, mData.size(), &mData[0][0]);
}

template <>
void DataUniform<glm::mat2>::applyData() const
{
	glUniformMatrix4fv(mLocation, mData.size(), false, &mData[0][0][0]);
}

template <>
void DataUniform<glm::mat3>::applyData() const
{
	glUniformMatrix4fv(mLocation, mData.size(), false, &mData[0][0][0]);
}

template <>
void DataUniform<glm::mat4>::applyData() const
{
	glUniformMatrix4fv(mLocation, mData.size(), false, &mData[0][0][0]);
}

typedef DataUniform<unsigned int> Sampler2DUniform;

}
