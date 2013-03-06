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

#include "Light.hpp"

namespace Forge {

Light::Light() :
	position(0.0f),
	color(0.0f),
	exponent(0.0f),
	direction(0.0f),
	cutoff(0.0f),
	falloff(0.0f)
{
	attenuation.constant =	0.1f;
	attenuation.linear =	0.1f;
	attenuation.quadratic =	0.00025f;
}

}
