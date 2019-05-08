#include "ShaderManager.h"
#include "RocketShader.h"

//vector<string> Manager::airports;
std::vector<RocketShader*> ShaderManager::mShaderList;


void ShaderManager::buildShaders()
{
	for (auto shader : mShaderList)
	{
		shader->init();

		//reassignVariables()
	}
}

void ShaderManager::useShaders()
{
	for (auto shader : mShaderList)
	{
		shader->use();
	}
}
