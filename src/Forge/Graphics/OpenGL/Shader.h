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

#include <string>

namespace Forge {

class Shader
{
public:
	enum class Type {
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        GEOMETRY_SHADER,
        TESSELLATION_CONTROL,
        TESSELLATION_EVALUATION
    };

	Shader();
	~Shader();

	void create(Shader::Type type);
	void loadCode(const std::string& file);
    const int compile();

    unsigned int getId()
	{
		return mId;
	}

	std::string getInfoLog() const;

private:
	void printInfoLog() const;

    unsigned int mId;
    int mType;
};

} // namespace Forge

#endif // SHADER_H
