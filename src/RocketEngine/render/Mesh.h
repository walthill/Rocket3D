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

#include "../util/EngineUtils.h"
#include <rkm/Vector2.h>
#include <rkm/Vector3.h>
#include <rkm/Mat4.h>
#include "buffers/Buffer.h"

class VertexArray;
class Texture2D;
class RK_Shader;

/* Vertex Data */
struct Vertex {
	rkm::Vector3 position, normal;
	rkm::Vector2 texCoords;
};

/* Contains all the mesh's vertices, indices, & textures */
struct MeshData {
	int instanceCount = 0;
	rkm::Mat4* matrices = nullptr;;
	std::vector<Vertex> vertices;
	std::vector<uint32> indices;
	std::vector<Texture2D*> textures;
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
		const std::string mDIFFUSE_UNIFORM_NAME = "texture_diffuse";
		const std::string mSPECULAR_UNIFORM_NAME = "texture_specular";
		const std::string mNORMAL_UNIFORM_NAME = "texture_normal";

		std::shared_ptr<VertexArray> mMeshVA;
		MeshData mMeshData;

		const BufferLayout mMeshLayout = {
			{ShaderDataType::Float3, "aPos"},
			{ShaderDataType::Float3, "aNormal"},
			{ShaderDataType::Float2, "aTexCoords"}
		};

		const BufferLayout mInstancedLayout = {
			{ShaderDataType::Float4, "aInstanceMatrix",1},
			{ShaderDataType::Float4, "aInstanceMatrix",1},
			{ShaderDataType::Float4, "aInstanceMatrix",1},
			{ShaderDataType::Float4, "aInstanceMatrix",1}
		};

		/***
			* Initializes mesh vertex positions, normals, and texture coordinates using OpenGL functions
		***/
		void initialize();
};

#endif //!MESH_H