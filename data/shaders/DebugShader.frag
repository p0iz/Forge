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

#version 330

in vec4 ex_Color;
out vec4 out_Color;

void main(void)
{
	out_Color = ex_Color;
	/*float greyscale = float(0.30*ex_Color.r + 0.59*ex_Color.g + 0.11*ex_Color.b);
	out_Color.r = greyscale * 1.20;
	out_Color.g = greyscale * 1.05;
	out_Color.b = greyscale * 0.75;*/
}
