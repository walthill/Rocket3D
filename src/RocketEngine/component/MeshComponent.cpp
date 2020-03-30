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
	if(mMeshData.modelName != "null" && mMeshData.modelName != "")
		mMeshData.mesh = new Model(modelFileLocation + mMeshData.modelName + "/" + mMeshData.modelName + ".obj");
}


void MeshComponent::cleanup()
{
	delete mMeshData.mesh;
}

Model* MeshComponent::getMesh()
{
	return mMeshData.mesh;
}

void MeshComponent::process(rkm::Vector3 position, rkm::Vector3 scale, rkm::Vector3 rotatonAxis, float rotationAngle)
{
 	modelMatrixValues = rkm::Mat4::identity;

	modelMatrixValues = rkm::Mat4::translate(modelMatrixValues, position);
	modelMatrixValues = rkm::Mat4::rotate(modelMatrixValues, rotationAngle, rotatonAxis);
	modelMatrixValues = rkm::Mat4::scale(modelMatrixValues, scale);
}

void MeshComponent::render(ShaderManager* shaderMan)
{		
	shaderMan->useShaderByKey(mMeshData.shaderKey);
	shaderMan->setShaderMat4(MATRIX_NAME, modelMatrixValues);

	if(mIsEnabled && mMeshData.mesh != nullptr)	
		mMeshData.mesh->drawModel(mMeshData.shader);
}

void MeshComponent::setMeshVisible(bool show)
{
	mIsEnabled = show;
}