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

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

namespace Forge {

class Shader
{
public:
	Shader();
	~Shader();

	void create(GLint type);
	void loadCode(std::string file);
	const GLint compile();

	GLuint getId()
	{
		return mId;
	}

	std::string getInfoLog() const;

private:
	void printInfoLog() const;

	GLuint mId;
	GLint mType;
};

} // namespace Forge

#endif // SHADER_H
