#include "ShaderManager.h"
#include "RK_Shader.h"

std::map<ShaderKey, RK_Shader*> ShaderManager::mShaderList;

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

void ShaderManager::useShaders()
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.begin();

	if (iter != mShaderList.end())
	{
		iter->second->use();
	}
}

void ShaderManager::useShaderByKey(ShaderKey key)
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		iter->second->use();
		mShaderInUse = key;
	}
}


void ShaderManager::setShaderInt(std::string intName, int value)
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.find(mShaderInUse);

	if (iter != mShaderList.end())
	{
		iter->second->setInt(intName, value);
	}

}

void ShaderManager::setShaderBool(std::string boolName, bool value)
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.find(mShaderInUse);

	if (iter != mShaderList.end())
	{
		iter->second->setBool(boolName, value);
	}
}

void ShaderManager::setShaderFloat(std::string floatName, float value)
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.find(mShaderInUse);

	if (iter != mShaderList.end())
	{
		iter->second->setFloat(floatName, value);
	}
}


void ShaderManager::setShaderMat4(std::string matrixName, const Mat4 &mat)
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.find(mShaderInUse);

	if (iter != mShaderList.end())
	{
		iter->second->setMat4(matrixName, mat);
	}
}

void ShaderManager::setShaderVec3(std::string vecName, const Vector3 &vec)
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.find(mShaderInUse);

	if (iter != mShaderList.end())
	{
		iter->second->setVec3(vecName, vec);
	}
}

void ShaderManager::setShaderVec3(std::string vecName, float x, float y, float z)
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.find(mShaderInUse);

	if (iter != mShaderList.end())
	{
		Vector3 vec = Vector3(x,y,z);
		iter->second->setVec3(vecName, vec);
	}
}

RK_Shader* ShaderManager::getShaderByKey(ShaderKey key)
{
	std::map<ShaderKey, RK_Shader*>::iterator iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		return iter->second;
	}

	return nullptr;
}