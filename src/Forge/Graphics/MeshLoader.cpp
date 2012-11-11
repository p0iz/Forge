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
#include "Mesh.h"

#include "Vertex.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>

namespace Forge {

Mesh* MeshLoader::loadObjModel(
		const char *objFile)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> positionIndices;
	std::vector<GLuint> uvIndices;
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
			glm::vec3 pos;
			glm::vec2 uv;
			switch (readLine[0])
			{
			case 'v':
				{
					switch (readLine[1])
					{
					case ' ':
						sscanf(readLine.c_str(), "v %f %f %f", &pos[0], &pos[1], &pos[2]);
						positions.push_back(pos);
						break;
					case 't':
						sscanf(readLine.c_str(), "vt %f %f", &uv[0], &uv[1]);
						uvs.push_back(uv);
						break;
					case 'n':
						sscanf(readLine.c_str(), "vn %f %f %f", &pos[0], &pos[1], &pos[2]);
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
					uvIndices.push_back(t[0]-1);
					normalIndices.push_back(n[0]-1);
					positionIndices.push_back(v[1]-1);
					uvIndices.push_back(t[1]-1);
					normalIndices.push_back(n[1]-1);
					positionIndices.push_back(v[2]-1);
					uvIndices.push_back(t[2]-1);
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
		GLuint iv, it, in;
		iv = positionIndices[i];
		it = uvIndices[i];
		in = normalIndices[i];
		Vertex vertex(positions[iv], uvs[it], normals[in]);
		vertices.push_back(vertex);
		elements.push_back(i);
	}
	// Done, now we have a unified element vector and a vertex vector
	return new Mesh(vertices, elements);
}

} // namespace Forge
