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

#include "MeshLoader.h"

#include "Graphics/Mesh.h"
#include "Graphics/Vertex.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>

namespace Forge {

Mesh* MeshLoader::loadObjModel(
		const char *objFile)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> positionIndices;
	std::vector<GLuint> texIndices;
	std::vector<GLuint> normalIndices;
	// Read obj file and instantiate the drawable
	std::ifstream inputFile;
	inputFile.open(objFile);
	if (!inputFile.is_open())
	{
		std::stringstream error;
		error << "Could not open file: " << objFile;
		return nullptr;
	}

	std::string readLine;
	while (getline(inputFile, readLine).good())
	{
		if (readLine.length() > 0)
		{
			// Create position, texture and normal data vectors
			std::string identifier;
			std::stringstream lineStream(readLine);
			lineStream >> identifier;
			glm::vec3 pos;
			glm::vec2 texCoord;
			switch (identifier[0])
			{
			case 'v':
				{
					switch(identifier[1])
					{
					case '\0':
						lineStream >> pos.x >> pos.y >>pos.z;
						positions.push_back(pos);
						break;
					case 't':
						lineStream >> texCoord.s >>texCoord.t;
						texCoords.push_back(texCoord);
						break;
					case 'n':
						lineStream >> pos.x >> pos.y >>pos.z;
						normals.push_back(pos);
						break;
					}
					break;
				}
			case 'f':
				{
					// Create index vectors
					GLuint v[3],t[3],n[3];
					sscanf(readLine.c_str(),"f %u/%u/%u %u/%u/%u %u/%u/%u", &v[0], &t[0], &n[0], &v[1], &t[1], &n[1], &v[2], &t[2], &n[2]);
					positionIndices.push_back(v[0]-1);
					texIndices.push_back(t[0]-1);
					normalIndices.push_back(n[0]-1);
					positionIndices.push_back(v[1]-1);
					texIndices.push_back(t[1]-1);
					normalIndices.push_back(n[1]-1);
					positionIndices.push_back(v[2]-1);
					texIndices.push_back(t[2]-1);
					normalIndices.push_back(n[2]-1);
					break;
				}
			}
		}
	}

	// After creating indices, generate a unified element vector and a packed vertex vector

	std::vector<Vertex> vertices;
	std::vector<GLuint> elements;

	for (unsigned int i = 0; i < positionIndices.size() ; ++i)
	{
		// Create a vertex from the individual indices
		Vertex vertex(
			positions[positionIndices[i]], texCoords[texIndices[i]], normals[normalIndices[i]]);
		vertices.push_back(vertex);
		elements.push_back(i);
	}
	// Done, now we have a unified element vector and a vertex vector
	return new Mesh(vertices, elements);
}

} // namespace Forge
