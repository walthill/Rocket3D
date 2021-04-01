/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 ShaderManager.cpp
	=========================

********/

#include "ShaderManager.h"

std::map<ShaderKey, RK_Shader*> ShaderManager::mShaderList;

ShaderManager::ShaderManager()
{
	mpCurrentShader = nullptr;
	mShaderList = {}; 
}

ShaderManager::~ShaderManager()
{
	clean();
}

void ShaderManager::clean()
{
	std::map<ShaderKey, RK_Shader*>::iterator iter;

	for (iter = mShaderList.begin(); iter != mShaderList.end(); ++iter)
	{
		delete iter->second;
	}
}

void ShaderManager::buildShaders()
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.begin();

	if (iter != mShaderList.end())
	{
		iter->second->init();
	}
}

void ShaderManager::useShaderByKey(const ShaderKey& key)
{
	if (key != mShaderInUse)
	{
		const auto& iter= mShaderList.find(key);

		if (iter != mShaderList.end())
		{
			mpCurrentShader = iter->second;
			mpCurrentShader->use();
			mShaderInUse = key;
		}
	}
}

void ShaderManager::setShaderInt(const std::string& intName, int value)
{
	mpCurrentShader->setInt(intName, value);
}

void ShaderManager::setShaderBool(const std::string& boolName, bool value)
{
	mpCurrentShader->setBool(boolName, value);
}

void ShaderManager::setShaderFloat(const std::string& floatName, float value)
{
	mpCurrentShader->setFloat(floatName, value);
}


void ShaderManager::setShaderMat4(const std::string& matrixName, const rkm::Mat4 &mat)
{
	mpCurrentShader->setMat4(matrixName, mat);
}

void ShaderManager::setShaderVec3(const std::string& vecName, const rkm::Vector3 &vec)
{
	mpCurrentShader->setVec3(vecName, vec);
}

void ShaderManager::setShaderVec3(const std::string& vecName, float x, float y, float z)
{
	mpCurrentShader->setVec3(vecName, rkm::Vector3(x, y, z));
}


void ShaderManager::setShaderVec2(const std::string& vecName, float x, float y)
{
	mpCurrentShader->setVec2(vecName, rkm::Vector2(x, y));
}

void ShaderManager::setShaderVec2(const std::string& vecName, const rkm::Vector2& vec)
{
	mpCurrentShader->setVec2(vecName, vec);
}


RK_Shader* ShaderManager::getShaderByKey(const ShaderKey& key)
{
	const auto& iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		return iter->second;
	}
	else
	{
		RK_CORE_ERROR_ALL("RK_Shader::Shader name invalid: " + key);
	}

	return nullptr;
}