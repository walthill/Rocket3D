#include "Mesh.h"
#include "../core/RenderCore.h"
#include "../shader/RK_Shader.h"
#include "buffers/VertexArray.h"
#include "buffers/Texture.h"
#include <glad/glad.h>

Mesh::Mesh(MeshData data)
{
	this->mMeshData.instanceCount = data.instanceCount;
	this->mMeshData.matrices = data.matrices;
	this->mMeshData.vertices = data.vertices;
	this->mMeshData.indices = data.indices;
	this->mMeshData.textures = data.textures;
	initialize();
}

void Mesh::drawMesh(RK_Shader* shader)
{
	// bind appropriate textures
	uint32 diffuseNr = 1;
	uint32 specularNr = 1;
	uint32 normalNr = 1;
	uint32 heightNr = 1;

	uint32 i;
	for (i = 0; i < mMeshData.textures.size(); i++)
	{
		RenderCommand::setActiveTexture(Renderer::TextureChannel::TEX_CHANNEL0, i); // activate proper texture unit before binding

		std::string name = "";
		// retrieve texture number (the N in diffuse_textureN)
		switch (mMeshData.textures[i]->getType())
		{
			case Renderer::TextureType::DIFFUSE:		name = mDIFFUSE_UNIFORM_NAME + std::to_string(diffuseNr++);		break;
			case Renderer::TextureType::SPECULAR:		name = mSPECULAR_UNIFORM_NAME + std::to_string(specularNr++);	break;
			case Renderer::TextureType::NORMAL:			name = mNORMAL_UNIFORM_NAME + std::to_string(normalNr++);		break;
			//case Renderer::TextureType::SPRITE:		name = mDIFFUSE_UNIFORM_NAME + std::to_string(diffuseNr++); break;
		}

		shader->setInt(name, i); // now set the sampler to the correct texture unit
		mMeshData.textures[i]->bind();
	}

	// draw mesh
	mMeshData.instanceCount == 1 ? RenderCore::submit(mMeshVA) : RenderCore::submitInstanced(mMeshVA, mMeshData.instanceCount);
	RenderCommand::setActiveTexture(Renderer::TextureChannel::TEX_CHANNEL0);
}

void Mesh::initialize()
{
	std::shared_ptr<VertexBuffer> mMeshVB, mInstancedVB;
	std::shared_ptr<IndexBuffer> mMeshIB;

	mMeshVA.reset(VertexArray::create());
	mMeshVB.reset(VertexBuffer::create(&mMeshData.vertices[0], sizeof(Vertex) * mMeshData.vertices.size()));
	mMeshVB->setLayout(mMeshLayout);
	mMeshVA->addVertexBuffer(mMeshVB);
	
	if (mMeshData.instanceCount > 1)
	{
		mInstancedVB.reset(VertexBuffer::create(&mMeshData.matrices[0], mMeshData.instanceCount * sizeof(rkm::Mat4)));
		mInstancedVB->setLayout(mInstancedLayout);
		mMeshVA->addVertexBuffer(mInstancedVB);
	}
	mMeshVA->processVertexBuffers();

	mMeshIB.reset(IndexBuffer::create(&mMeshData.indices[0], mMeshData.indices.size() / sizeof(uint32)));
	mMeshVA->setIndexBuffer(mMeshIB);
	
	mMeshVA->unbind();
}


