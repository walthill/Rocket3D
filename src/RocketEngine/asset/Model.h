#ifndef MODEL_H
#define MODEL_H

#include "../render/Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "image/RocketImgLoader.h"

struct ModelData {
	std::vector<Mesh> meshes;
	std::string directory;
};


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
	//TODO: add gamma correction code after lighting tutorial

	public:
		Model(std::string path)
		{
			initialize(path);
		};
		void drawModel(RK_Shader* shader)
		{
			for (auto i = 0; i < mModelData.meshes.size(); i++)
				mModelData.meshes[i].drawMesh(shader);
		};

	private:
		ModelData mModelData;
		std::vector<Texture> texturesLoaded;

		void initialize(std::string path)
		{
			Assimp::Importer importer;
			const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);


			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
				return;
			}
			mModelData.directory = path.substr(0, path.find_last_of('/'));

			processNode(scene->mRootNode, scene);
		};

		void processNode(aiNode* node, const aiScene *scene)
		{
			// process all the node's meshes (if any)
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
				mModelData.meshes.push_back(assimpToMesh(mesh, scene));
			}

			// process meshes for each child
			for (unsigned int i = 0; i < node->mNumChildren; i++)
				processNode(node->mChildren[i], scene);
		};


		// process Assimp's data into a Mesh class object
		Mesh assimpToMesh(aiMesh *mesh, const aiScene *scene)
		{
			MeshData data;

			//Fill mesh vertices
			for (auto i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vert;
				Vector3 vector;
				Vector2 texVector;

				//Set position
				vector = Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
				vert.position = vector;
				
				vector = Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
				vert.normal = vector;
	
				//check for texture coordinates
				if (mesh->mTextureCoords[0])
				{
					texVector = Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
					vert.texCoords = texVector;
				}
				else
					vert.texCoords = Vector2::zero;	

				data.vertices.push_back(vert);
			}
			
			//Fill mesh indices
			for (auto i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (auto j = 0; j < face.mNumIndices; j++)
					data.indices.push_back(face.mIndices[j]);
			}

			if (mesh->mMaterialIndex >= 0) //see lighting tutorial for more
			{
				aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

				//Diffuse maps
				std::vector<Texture> diffuseMaps = getTexturesFromMaterial(material, aiTextureType_DIFFUSE, "texture_diffuse");
				data.textures.insert(data.textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				//Specular maps
				std::vector<Texture> specularMaps = getTexturesFromMaterial(material, aiTextureType_SPECULAR, "texture_specular");
				data.textures.insert(data.textures.end(), specularMaps.begin(), specularMaps.end());


				//TODO: add other material map types
			}

			return Mesh(data);
		};

		std::vector<Texture> getTexturesFromMaterial(aiMaterial *mat, aiTextureType type, std::string typeName)
		{
			std::vector<Texture> textures;
			for (auto i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);
				bool loadFromMemory = false;

				//Check if texture has alread been loaded and use that data if so
				for (auto j = 0; j < texturesLoaded.size(); j++)
				{
					if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
					{
						textures.push_back(texturesLoaded[j]);
						loadFromMemory = true;
						break;
					}
				}

				if (!loadFromMemory) //load in new texture from file
				{
					Texture texture;
					std::string str2 = (std::string)str.C_Str();

					// Remove directory if present.
					// Do this before extension removal incase directory has a period character.
					const size_t last_slash_idx = str2.find_last_of("\\/");
					if (std::string::npos != last_slash_idx)
					{
						str2.erase(0, last_slash_idx + 1);
					}
					texture.id = TextureFromFile(str2.c_str(), mModelData.directory);
					texture.type = typeName;
					texture.path = str2.c_str();
					textures.push_back(texture);
					texturesLoaded.push_back(texture); // add to loaded textures
				}
			}
			return textures;
		};
};


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
	std::string filename = (std::string)path;
	filename = directory + '/' + filename;

	TextureId id;
	glGenTextures(1, &id);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "ERROR::Texture::Failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return id;
}


#endif // !MODEL_H
