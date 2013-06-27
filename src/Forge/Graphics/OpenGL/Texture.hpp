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

class Texture {
public:
	enum class Target {
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_3D,
		TEXTURE_CUBE
	};

	enum class Unit {
		TEXTURE0,
		TEXTURE1,
		TEXTURE2,
		TEXTURE3,
		TEXTURE4,
		TEXTURE5,
		TEXTURE6,
		TEXTURE7
	};

	enum class Wrap {
		CLAMP_EDGE,
		REPEAT,
		REPEAT_MIRROR
	};

	enum class Filter {
		NEAREST,
		LINEAR,
		NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR
	};

	// Use to create texture handle from already-loaded data
	Texture(int target, unsigned int name);

	void setWrapping(Wrap s);
	void setWrapping(Wrap s, Wrap t);
	void setWrapping(Wrap s, Wrap t, Wrap r);

	void setFiltering(Filter min, Filter mag);

	void create(Target type);
	void destroy();

	void bind();
	void release();

	static void setActiveUnit(Unit unit);

private:
	unsigned int mName;
	int mTarget;

	static int getGLType(Target target);
	static int getGLUnit(Unit unit);
	static int getGLWrap(Wrap wrap);
	static int getGLFilter(Filter filter);
};

}
