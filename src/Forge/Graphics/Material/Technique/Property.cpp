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

#include "Property.h"

namespace Forge {

PropertyValue::PropertyValue(float value) { mValue.fval = value; }
PropertyValue::PropertyValue(double value) { mValue.fval = value; } // Loss of precision
PropertyValue::PropertyValue(int value) { mValue.ival = value; }
PropertyValue::PropertyValue(unsigned int value) { mValue.uval = value; }

PropertyValue::operator float() const {
	if (!this)
		return 0.0f;
	return mValue.fval;
}

PropertyValue::operator int() const {
	if (!this)
		return -1;
	return mValue.ival;
}

PropertyValue::operator unsigned int() const {
	if (!this)
		return 0;
	return mValue.uval;
}

PropertyValue::operator const float*() const {
	if (!this)
		return nullptr;
	return &mValue.fval;
}

PropertyValue::operator const int*() const {
	if (!this)
		return nullptr;
	return &mValue.ival;
}

PropertyValue::operator const unsigned int*() const {
	if (!this)
		return nullptr;
	return &mValue.uval;
}

}
