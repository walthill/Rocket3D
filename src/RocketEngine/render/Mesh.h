/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This class makes use of tutorials from Learn OpenGL
	(https://learnopengl.com)

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 Mesh.h
	=========================

********/

#ifndef MESH_H
#define MESH_H

#include <rkm/Vector2.h>
#include <rkm/Vector3.h>
#include <vector>
#include <string>
#include "../shader/RK_Shader.h"

typedef unsigned int TextureId;

/* Vertex Data */
struct Vertex {
	rkm::Vector3 position, normal;
	rkm::Vector2 texCoords;
};

/* Texture Data */
struct TextureData {
    TextureId id = -1;
    std::string type, path;
};

/* Contains all the mesh's vertices, indices, & textures */
struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureData> textures;
};

class Mesh
{
	public:
		/***
			* Constructor that initializes mesh and sets mesh data
		***/
		Mesh(MeshData data);

		/***
			* Render mesh triangles and set texture values on the fragment shader
		***/
		void drawMesh(RK_Shader* shader);

	private:
		MeshData mMeshData;
		unsigned int VAO, VBO, EBO;

		/***
			* Initializes mesh vertex positions, normals, and texture coordinates using OpenGL functions
		***/
		void initialize();
};

#endif //!MESH_H