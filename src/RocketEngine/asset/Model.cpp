#include "Model.h"


Model::Model(std::string path)
{
	initialize(path);
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
		std::vector<Texture> diffuseMaps = getTexturesFromMaterial(material, aiTextureType_DIFFUSE, "texture_diffuse");
		data.textures.insert(data.textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		//Specular maps
		std::vector<Texture> specularMaps = getTexturesFromMaterial(material, aiTextureType_SPECULAR, "texture_specular");
		data.textures.insert(data.textures.end(), specularMaps.begin(), specularMaps.end());


		//TODO: add other material map types
	}

	return Mesh(data);
}

/*
	* Takes in a material object. Accesses & stores textures from that material
*/
std::vector<Texture> Model::getTexturesFromMaterial(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool loadFromMemory = false;

		//Check if texture has alread been loaded and use that data if so
		for (unsigned int j = 0; j < texturesLoaded.size(); j++)
		{
			if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded[j]);
				loadFromMemory = true;
				break;
			}
		}

		//load in new texture from file
		if (!loadFromMemory)
		{
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), mModelData.directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			texturesLoaded.push_back(texture);
		}
	}
	return textures;
}


/*
	* Loads in textures from the given file path and
	stores the textures in an OpenGL-compatible form
*/
unsigned int Model::TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = (std::string)path;
	filename = directory + '/' + filename;

	TextureId id;
	glGenTextures(1, &id);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format = -1;
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
		RK_CORE_ERROR_ALL("ERROR::Texture::Failed to load at path: " + (std::string)path);
		stbi_image_free(data);
	}

	return id;
}