#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "../logging/RK_Log.h"
#include "../render/Renderer.h"
#include "../render/buffers/Texture.h"
#include "../render/buffers/VertexArray.h"

Model::Model(std::string path, int instanceCount, rkm::Mat4* matrices) :
	mInstanceCount(instanceCount), mMatrices(matrices)
{
	initialize(path);
}


Model::~Model()
{
	clean();
}

void Model::clean()
{
	for (size_t i = 0; i < texturesLoaded.size(); i++)
	{
		delete texturesLoaded[i];
	}
}

/*
	* Render meshes to display model on-screen
*/
void Model::drawModel(RK_Shader* shader)
{
	for (unsigned int i = 0; i < mModelData.meshes.size(); i++)
		mModelData.meshes[i].drawMesh(shader);
}

void Model::initialize(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string err = "ERROR::ASSIMP::";
		err.append(importer.GetErrorString());
		RK_CORE_ERROR_ALL(err);
		return;
	}
	mModelData.directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

/*
	* Recursive function that creates a tree of mesh nodes
	from the model files to be stored in a vector
*/
void Model::processNode(aiNode* node, const aiScene* scene)
{
	unsigned int i;
	// process all the node's meshes (if any)
	for (i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		mModelData.meshes.push_back(assimpToMesh(mesh, scene));
	}

	// process meshes for each child
	for (i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}


/*
	* Process Assimp-based vertex data and store in a Mesh class object
*/
Mesh Model::assimpToMesh(aiMesh* mesh, const aiScene* scene)
{
	MeshData data;

	data.instanceCount = mInstanceCount;
	data.matrices = mMatrices;

	Vertex vert;
	rkm::Vector3 vector;
	rkm::Vector2 texVector;
	unsigned int i;

	//Fill mesh vertices
	for (i = 0; i < mesh->mNumVertices; i++)
	{
		//Set position
		vector = rkm::Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vert.position = vector;

		vector = rkm::Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vert.normal = vector;

		//check for texture coordinates
		if (mesh->mTextureCoords[0])
		{
			texVector = rkm::Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			vert.texCoords = texVector;
		}
		else
			vert.texCoords = rkm::Vector2::zero;

		data.vertices.push_back(vert);
	}

	//Fill mesh indices
	for (i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			data.indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0) //see lighting tutorial for more
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		//Diffuse maps
		std::vector<Texture2D*> diffuseMaps = getTexturesFromMaterial(material, aiTextureType_DIFFUSE, Renderer::TextureType::DIFFUSE);
		data.textures.insert(data.textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		//Specular maps
		std::vector<Texture2D*> specularMaps = getTexturesFromMaterial(material, aiTextureType_SPECULAR, Renderer::TextureType::SPECULAR);
		data.textures.insert(data.textures.end(), specularMaps.begin(), specularMaps.end());


		//TODO: add other material map types
	}

	return Mesh(data);
}

/*
	* Takes in a material object. Accesses & stores textures from that material
*/
std::vector<Texture2D*> Model::getTexturesFromMaterial(aiMaterial* mat, aiTextureType type, int typeName)
{
	std::vector<Texture2D*> textures = std::vector<Texture2D*>();
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool loadFromMemory = false;

		//Check if texture has alread been loaded and use that data if so
		for (unsigned int j = 0; j < texturesLoaded.size(); j++)
		{
			if (std::strcmp(texturesLoaded[j]->getPath().data(), str.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded[j]);
				loadFromMemory = true;
				break;
			}
		}

		//load in new texture from file
		if (!loadFromMemory)
		{
			std::string filename = (std::string)str.C_Str();
			filename = mModelData.directory + '/' + filename;
			
			textures.push_back(Texture2D::create(filename, typeName, Texture::WrapType::REPEAT, Texture::WrapType::REPEAT,
							   Texture::MinifyFilter::LINEAR_MIPMAP_LINEAR, Texture	::MagnifyFilter::MAG_LINEAR));
			
			texturesLoaded.push_back(textures[textures.size()-1]);
		}
	}
	return textures;
}