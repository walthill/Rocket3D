#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "../../RocketEngine/asset/Model.h"

MeshComponent::MeshComponent(const ComponentId& id) :
	Component(id)
{
}

MeshComponent::~MeshComponent()
{
	cleanup();
}

void MeshComponent::load()
{
	mMeshData.mesh = new Model(modelFileLocation + mMeshData.modelName + "/" + mMeshData.modelName + ".obj");
}


void MeshComponent::cleanup()
{
	delete mMeshData.mesh;
}

void MeshComponent::render(Vector3 position, Vector3 scale, Vector3 rotatonAxis, float rotationAngle)
{	
	modelMatrixValues = Mat4::identity;

	modelMatrixValues = Mat4::translate(modelMatrixValues, position);
	modelMatrixValues = Mat4::rotate(modelMatrixValues, rotationAngle, rotatonAxis);
	modelMatrixValues = Mat4::scale(modelMatrixValues, scale);

	mMeshData.shader->use();
	mMeshData.shader->setMat4(MATRIX_NAME, modelMatrixValues);

	if(mMeshData.mesh != nullptr)	
		mMeshData.mesh->drawModel(mMeshData.shader);
}
