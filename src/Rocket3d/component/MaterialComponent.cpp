#include "MaterialComponent.h"
#include "../../RocketEngine/shader/ShaderManager.h"
#include "../../RocketEngine/shader/RK_Shader.h"

MaterialComponent::MaterialComponent(ShaderManager * man, ShaderType shaderType)
{
	if (shaderType == STANDARD_SHADER)
	{
		mShader = man->getShaderByKey(STANDARD_SHADER_KEY);
	}

	man = nullptr;
}

void MaterialComponent::setMeshProperties(Mat4 modelMatrixValue)
{
	const std::string MATRIX_NAME = "model";
	mShader->use();
	mShader->setMat4(MATRIX_NAME, modelMatrixValue);
}

