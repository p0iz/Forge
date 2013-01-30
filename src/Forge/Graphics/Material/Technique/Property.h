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
 * Copyright 2013 Tommi Martela
 *
 */

#pragma once

#include <vector>

namespace Forge {

/* Nasty class that can be a pointer-to or a value depending on the implicit conversions
 * - used for storing a single property value
 */
class PropertyValue
{
public:
	PropertyValue(float value);
	PropertyValue(double value);
	PropertyValue(int value);
	PropertyValue(unsigned int value);

	operator float() const;
	operator int() const;
	operator unsigned int() const;
	operator const float*() const;
	operator const int*() const;
	operator const unsigned int*() const;

private:
	typedef union
	{
		float fval;
		int ival;
		unsigned int uval;
	} PropertyValueType;

	PropertyValueType mValue;
};

/* This vector describes a single property */
typedef std::vector<PropertyValue> Property;

}
