#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "../shader/RK_Shader.h"

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
	if (mMeshData.modelName != "null" && mMeshData.modelName != "")
	{
		std::string folderName = mMeshData.modelName.substr(0, mMeshData.modelName.find('.'));
		mMeshData.mesh = new Model(modelFileLocation + folderName + "/" + mMeshData.modelName);
	}
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

void MeshComponent::render()
{
	if (mMeshData.shader != nullptr)
	{
		mMeshData.shader->use();
		mMeshData.shader->setMat4(MATRIX_NAME, modelMatrixValues);

		if (mIsEnabled && mMeshData.mesh != nullptr)
			mMeshData.mesh->drawModel(mMeshData.shader);
	}
}

void MeshComponent::setMeshVisible(bool show)
{
	mIsEnabled = show;
}