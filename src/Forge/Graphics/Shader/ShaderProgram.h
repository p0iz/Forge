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

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

namespace Forge {

// Class for shader programs
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void create();
	const int link();

	const unsigned int getAttribLocation(const char* attribName) const;
	const unsigned int getUniformLocation(const char* uniformName) const;
	const unsigned int getId();

	const std::string getProgramInfoLog() const;

	void setVertexShader(unsigned int shader);
	void setFragmentShader(unsigned int shader);

	void use() const;

	static void release();

private:
	unsigned int mId;
	unsigned int mVertexShaderId;
	unsigned int mFragmentShaderId;
};

} // namespace Forge

#endif // SHADERPROGRAM_H
