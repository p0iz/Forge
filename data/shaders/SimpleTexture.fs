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
in vec3 view_space_normal;
in vec3 view_space_vertex;

out vec3 color;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;

uniform sampler2D albedo;

struct Light
{
	vec4 position;
	vec4 color;
	float constant;
	float linear;
	float quadratic;
};

layout (std140) uniform Lights
{
  Light lights[8]; // max 8 lights per mesh
};

in float attenuation[8];

uniform vec4 ambient;

void main(void)
{
	vec3 texColor = texture2D(albedo, UV).rgb;
	vec3 lighting = ambient.rgb * ambient.a * texColor * materialAmbient;
	for (int i = 0; i < lights.length(); ++i) {
		vec3 view_space_light = normalize(-vec3(lights[i].position));
		float diffuseIntensity = dot(view_space_normal, view_space_light);
		if (diffuseIntensity > 0.0f) {
			vec3 lightContribution = vec3(0.0f);
			vec3 halfway = normalize(view_space_light + view_space_vertex);
			float specularIntensity = pow(max(0.0f, dot(view_space_normal, halfway)), materialShininess);
			lightContribution += materialDiffuse * texColor * diffuseIntensity;
			lightContribution += materialSpecular * specularIntensity;
			lightContribution *= (lights[i].color.rgb * lights[i].color.a);
			if (lights[i].position.w > 0.0f) {
				lightContribution *= attenuation[i];
			}
			lighting += lightContribution;
		}
	}
	color = texture2D(albedo, UV).rgb * lighting;
}
