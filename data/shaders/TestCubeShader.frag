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

in vec2 UV;
in vec3 viewNormal;
in vec3 viewVertex; // View vector

out vec3 color;

uniform vec4 materialAmbient;
uniform vec4 materialDiffuse;
uniform vec4 materialSpecular;
uniform float materialShininess;

uniform sampler2D albedo;

uniform mat4 WorldViewMatrix;

struct DirectionalLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 direction;
};

uniform DirectionalLight directional;

void main(void)
{
	vec3 halfway = normalize(directional.direction + viewVertex);

	float diffuseIntensity =
		max(0.0f, dot(viewNormal, directional.direction));

	float specularIntensity = 
		pow(max(0.0f, dot(viewNormal, halfway)), 128.0f);

	color = 
		texture2D(albedo, UV).rgb * 
		((directional.ambient.rgb * directional.ambient.a) + 
		(directional.diffuse.rgb * directional.diffuse.a * diffuseIntensity) +
		(specularIntensity * directional.specular.rgb * directional.specular.a));
}
