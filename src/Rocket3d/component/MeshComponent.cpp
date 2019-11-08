#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "../../RocketEngine/asset/Model.h"

MeshComponent::MeshComponent(std::string modelName)
{
	mMesh = new Model(modelFileLocation	+ modelName + "/" + modelName + ".obj");
}

MeshComponent::~MeshComponent()
{
	cleanup();
}


void MeshComponent::cleanup()
{
	delete mMesh;
}

void MeshComponent::render(Vector3 position, Vector3 scale, Vector3 rotatonAxis, float rotationAngle)
{	
	modelMatrixValues = Mat4::identity;

	modelMatrixValues = Mat4::translate(modelMatrixValues, position);
	modelMatrixValues = Mat4::rotate(modelMatrixValues, rotationAngle, rotatonAxis);
	modelMatrixValues = Mat4::scale(modelMatrixValues, scale);

	mMaterialComponent->setMeshProperties(modelMatrixValues); //assume this is model matrix
	mMesh->drawModel(mMaterialComponent->getShader());
}
