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

namespace Forge {

class Buffer {
public:
	enum class Target {
		UNIFORM_BUFFER,
		ELEMENT_BUFFER,
		VERTEX_BUFFER
	};

	enum class Usage {
		DYNAMIC_COPY,
		DYNAMIC_DRAW,
		DYNAMIC_READ,
		STATIC_COPY,
		STATIC_DRAW,
		STATIC_READ,
		STREAM_COPY,
		STREAM_DRAW,
		STREAM_READ
	};

	Buffer();

	void create(Target target);
	void destroy();
	void bind();

	void setData(size_t size, const void* data, Usage usage);
	void setSubData(unsigned int begin, unsigned int size, void* data);

	void setBindingPoint(unsigned int point);

	void release();
private:
	unsigned int mName;
	int mTarget;

	int getGLTarget(Target target);
	int getGLUsage(Usage usage);
};

}
