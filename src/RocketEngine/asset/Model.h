/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	The Rocket Engine code was written with
	help from the Learn OpenGL tutorials
	(https://learnopengl.com)

	This file makes use of the Assimp library to load models.
	(http://assimp.org/)

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 Model.h
	=========================

********/

#ifndef MODEL_H
#define MODEL_H

#include "../render/Mesh.h"
#include <assimp/scene.h>

struct ModelData {
	std::vector<Mesh> meshes;
	std::string directory;
};

class Model : public rkutil::Trackable
{
	//TODO: add gamma correction code after lighting tutorial
	public:
		/*
			* Constructor requires a path to the model for initialization
		*/
		Model(std::string path, int instanceCount = 1, rkm::Mat4* matrices = nullptr);

		~Model();

		void clean();

		/*
			* Render meshes to display model on-screen
		*/
		void drawModel(RK_Shader* shader);
		ModelData mModelData;

		std::vector<Texture2D*> texturesLoaded;
	private:
		
		int mInstanceCount;
		rkm::Mat4* mMatrices;


		/*
			* Initialize model data and store in a ModelData struct 
		*/
		void initialize(std::string path);

		/*
			* Recursive function that creates a tree of mesh nodes 
			from the model files to be stored in a vector
		*/
		void processNode(aiNode* node, const aiScene* scene);

		/*
			* Process Assimp-based vertex data and store in a Mesh class object
		*/
		Mesh assimpToMesh(aiMesh* mesh, const aiScene* scene);

		/*
			* Takes in a material object. Accesses & stores textures from that material
		*/
		std::vector<Texture2D*> getTexturesFromMaterial(aiMaterial* mat, aiTextureType type, int typeName);
};

#endif // !MODEL_H
