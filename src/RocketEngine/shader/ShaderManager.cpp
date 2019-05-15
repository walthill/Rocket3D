#include "ShaderManager.h"
#include "RocketShader.h"

std::map<ShaderKey, RocketShader*> ShaderManager::mShaderList;

ShaderManager::~ShaderManager()
{
	clean();
}

void ShaderManager::clean()
{
	std::map<ShaderKey, RocketShader*>::iterator iter;

	for (iter = mShaderList.begin(); iter != mShaderList.end(); ++iter)
	{
		delete iter->second;
	}
}

void ShaderManager::buildShaders()
{
	std::map<ShaderKey, RocketShader*>::iterator iter = mShaderList.begin();

	if (iter != mShaderList.end())
	{
		iter->second->init();
	}
}

void ShaderManager::useShaders()
{
	std::map<ShaderKey, RocketShader*>::iterator iter = mShaderList.begin();

	if (iter != mShaderList.end())
	{
		iter->second->use();
	}
}

void ShaderManager::useShaderByKey(ShaderKey key)
{
	std::map<ShaderKey, RocketShader*>::iterator iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		iter->second->use();
	}
}


void ShaderManager::setShaderInt(ShaderKey key, std::string intName, int value)
{
	std::map<ShaderKey, RocketShader*>::iterator iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		iter->second->setInt(intName, value);
	}

}

void ShaderManager::setShaderBool(ShaderKey key, std::string boolName, bool value)
{
	std::map<ShaderKey, RocketShader*>::iterator iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		iter->second->setBool(boolName, value);
	}
}

void ShaderManager::setShaderFloat(ShaderKey key, std::string floatName, float value)
{
	std::map<ShaderKey, RocketShader*>::iterator iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		iter->second->setFloat(floatName, value);
	}
}

void ShaderManager::setShaderMat4(ShaderKey key, std::string matrixName, const float *mat)
{
	std::map<ShaderKey, RocketShader*>::iterator iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		iter->second->setMat4(matrixName, mat);
	}
}

void ShaderManager::setShaderVec3(ShaderKey key, std::string vecName, float x, float y, float z)
{
	std::map<ShaderKey, RocketShader*>::iterator iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		float* arr = new float[3]{ x,y,z };
		iter->second->setVec3(vecName, arr);
	}
}



RocketShader* ShaderManager::getShaderByKey(ShaderKey key)
{
	std::map<ShaderKey, RocketShader*>::iterator iter = mShaderList.find(key);

	if (iter != mShaderList.end())
	{
		return iter->second;
	}

	return nullptr;
}