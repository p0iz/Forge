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

#include <unordered_map>

namespace Forge {

class VertexArray {
public:
	enum class ElementType {
		BYTE,
		SHORT,
		INT,
		FLOAT,
		DOUBLE,
		UNSIGNED_BYTE,
		UNSIGNED_SHORT,
		UNSIGNED_INT
	};

	VertexArray();

	void create();
	void destroy();
	void bind();

	void setAttribute(const unsigned int location,
					  const unsigned int elements,
					  const ElementType type,
					  const bool normalized,
					  const unsigned int stride,
					  const void* offset);

	void enableAttribute(unsigned int location);
	void disableAttribute(unsigned int location);

	static void release();
private:
	unsigned int mName;

	static int getGLType(ElementType);
};

}
