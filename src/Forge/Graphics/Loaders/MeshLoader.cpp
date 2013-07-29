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
#include "Graphics/Vertex.h"
#include "Util/Log.h"

#include <algorithm>
#include <fstream>
#include <sstream>


namespace Forge { namespace MeshLoader {

// Helper class to identify unique vertices
struct VertexIdentifier
{
    VertexIdentifier(int p, int t, int n, unsigned int element):
      mElement(element),
      mP(p),
      mT(t),
      mN(n)
    {
    }

    bool operator==(VertexIdentifier const& rhs) const
    {
      return mP == rhs.mP && mT == rhs.mT && mN == rhs.mN;
    }

    unsigned int mElement;

  private:
    int mP;
    int mT;
    int mN;
};

/* Parse a string of type "<pos>/<tex>/<nor>" and return true if at least <pos> was found */
void parseVertex(std::string const& vertex, int& posIndex, int& texIndex, int&norIndex)
{
  std::istringstream vertexStream(vertex);
  vertexStream >> posIndex;
  vertexStream.get();
  if (vertexStream.peek() == '/')
  {
    vertexStream.get();
    vertexStream >> norIndex;
  }
  else
  {
    vertexStream >> texIndex;
    vertexStream >> norIndex;
  }
}

MeshPtr loadMesh(const std::string& file)
{
  MeshPtr loadedMesh(nullptr);

  std::ifstream inputFile(file);
  if (!inputFile.is_open())
  {
    Log::error << "Could not open file '" << file << "'. Mesh loading failed.\n";
    return loadedMesh;
  }

  std::string meshName;

  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texCoords;

  std::vector<VertexIdentifier> vertexIds;
  std::vector<unsigned int> elements;
  unsigned int nextIndex = 0;

  std::vector<Vertex> vertices;

  while (!inputFile.eof())
  {
    std::string identifier;
    inputFile >> identifier;

    if (identifier == "o")
    {
      inputFile >> meshName;
    }
    else if (identifier == "v")
    {
      glm::vec3 position;
      inputFile >> position.x >> position.y >> position.z;
      positions.push_back(position);
    }
    else if (identifier == "vn")
    {
      glm::vec3 normal;
      inputFile >> normal.x >> normal.y >> normal.z;
      normals.push_back(normal);
    }
    else if (identifier == "vt")
    {
      glm::vec2 texCoord;
      inputFile >> texCoord.s >> texCoord.t;
      texCoords.push_back(texCoord);
    }
    else if (identifier == "f")
    {
      // V1: <position>/<texCoord>/<normal> V2: <position>/<texCoord>/<normal> V3: <position>/<texCoord>/<normal>
      for (int i = 0; i < 3; ++i)
      {
        int pos = -1;
        int tex = -1;
        int nor = -1;
        std::string vertex;
        inputFile >> vertex;
        parseVertex(vertex, pos, tex, nor);

        if (pos == -1)
        {
          Log::error << "Vertex definition must at least contain vertex position."
                        "Mesh loading failed.\n";
          return loadedMesh;
        }

        VertexIdentifier id(pos, tex, nor, nextIndex);
        auto idIter = std::find_if(
          vertexIds.begin(),
          vertexIds.end(),
          [&id](VertexIdentifier const& rhs){ return id == rhs; }
        );

        if (idIter == vertexIds.end())
        {
          // Not found in existing vertices, add new index
          glm::vec3 position = positions[pos];
          glm::vec2 texCoord;
          glm::vec3 normal;
          if (tex != -1)
          {
            texCoord = texCoords[tex];
          }
          if (nor != -1)
          {
            normal = normals[nor];
          }
          Vertex v(position, texCoord, normal);
          vertices.push_back(v);
          elements.push_back(id.mElement);

          vertexIds.push_back(id);
          ++nextIndex;
        }
        else
        {
          elements.push_back(idIter->mElement);
        }
      }
    }
    else
    {
      // Skip comments and unsupported identifiers
      while (!inputFile.eof() && inputFile.get() != '\n');
    }
  }

  loadedMesh.reset(new Mesh(vertices, elements));
  loadedMesh->setName(meshName);

  return loadedMesh;
}

}}
