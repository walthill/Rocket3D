#ifndef MESH_H
#define MESH_H

#include <RocketMath/Vector2.h>
#include <RocketMath/Vector3.h>
#include <vector>
#include <string>
#include "../shader/RK_Shader.h"
#include <glad/glad.h>

typedef unsigned int TextureId;

struct Vertex {
    Vector3 position, normal;
    Vector2 texCoords;
};

struct Texture {
    TextureId id;
    std::string type, path;
};

struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
};

class Mesh
{
	public:
		Mesh(MeshData data)
		{
			this->mMeshData.vertices = data.vertices;
			this->mMeshData.indices = data.indices;
			this->mMeshData.textures = data.textures;
			initialize();
		};

		void drawMesh(RK_Shader* shader)
		{
			// bind appropriate textures
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			unsigned int normalNr = 1;
			unsigned int heightNr = 1;
			
			unsigned int i;
			for (i = 0; i < mMeshData.textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
				// retrieve texture number (the N in diffuse_textureN)
				std::string number;
				std::string name = mMeshData.textures[i].type;
				
				if (name == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if (name == "texture_specular")
					number = std::to_string(specularNr++); // transfer unsigned int to stream
				else if (name == "texture_normal")
					number = std::to_string(normalNr++); // transfer unsigned int to stream
				else if (name == "texture_height")
					number = std::to_string(heightNr++); // transfer unsigned int to stream

														 // now set the sampler to the correct texture unit
				shader->setFloat((name + number), i);
				// and finally bind the texture
				glBindTexture(GL_TEXTURE_2D, mMeshData.textures[i].id);
			}

			// draw mesh
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, mMeshData.indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// always good practice to set everything back to defaults once configured.
			glActiveTexture(GL_TEXTURE0);
		};

	private:
		MeshData mMeshData;
		unsigned int VAO, VBO, EBO;

		void initialize()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, mMeshData.vertices.size() * sizeof(Vertex), &mMeshData.vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMeshData.indices.size() * sizeof(unsigned int),
						 &mMeshData.indices[0], GL_STATIC_DRAW);

			// vertex positions
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			// vertex normals
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			// vertex texture coords
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

			glBindVertexArray(0);
		};
};

#endif //!MESH_H