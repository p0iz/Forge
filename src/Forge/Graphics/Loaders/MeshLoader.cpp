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

#include "Util/Log.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>

namespace Forge { namespace MeshLoader {

Mesh* loadMesh(const std::string& file) {
	Mesh* loadedMesh = nullptr;
	Assimp::Importer importer;

	const aiScene* importedModel = importer.ReadFile(
				file, aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (importedModel == nullptr) {
		Log::error << "Error occurred while importing '" <<
					  file << "'' : " << importer.GetErrorString() << "\n";
	} else {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> elements;
		for (unsigned int cur_mesh = 0 ; cur_mesh < importedModel->mNumMeshes; ++ cur_mesh) {
			const aiMesh* mesh = importedModel->mMeshes[cur_mesh];
			// Load vertex data
			Vertex vertex;
			for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
				// Read position
				memcpy(vertex.position, &mesh->mVertices[i], sizeof(float) * 3);
				if (mesh->HasNormals()) {
					// Read normal
					memcpy(vertex.normal, &mesh->mNormals[i], sizeof(float) * 3);
				}
				if (mesh->HasTangentsAndBitangents()) {
					// Read tangent
					memcpy(vertex.tangent, &mesh->mTangents[i], sizeof(float) * 3);
					// Read bitangent
					memcpy(vertex.bitangent, &mesh->mBitangents[i], sizeof(float) * 3);
				}
				if (mesh->HasTextureCoords(0)) {
					// Read texture coordinates (currently just one texture supported)
					memcpy(vertex.texcoord, &mesh->mTextureCoords[0][i], sizeof(float) * 3);
				}
				vertices.push_back(vertex);
			}
			for (unsigned int face_index = 0 ; face_index < mesh->mNumFaces; ++face_index) {
				const aiFace& cur_face = mesh->mFaces[face_index];
				for (unsigned int elem_index = 0 ; elem_index < cur_face.mNumIndices; ++elem_index) {
					elements.push_back(mesh->mFaces[face_index].mIndices[elem_index]);
				}
			}
		}
		loadedMesh = new Mesh(vertices, elements);
	}
	return loadedMesh;
}

}}
