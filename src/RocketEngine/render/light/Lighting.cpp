#include "Lighting.h"
#include "../../shader/ShaderManager.h"
#include "../Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

Lighting::Lighting(ShaderKey key, ShaderManager* man, int numberOfPointLights)
{
	mLightingShaderKey = key;
	mShaderManagerHandle = man;
	initMaterialData();
	initLightingData(numberOfPointLights); //TODO: make parameter
}

void Lighting::initialize(ShaderKey key, ShaderManager* man, int numberOfPointLights)
{
	mLightingShaderKey = key;
	mShaderManagerHandle = man;
	initMaterialData();
	initLightingData(numberOfPointLights);
};

void Lighting::initMaterialData()
{
	mShaderManagerHandle->useShaderByKey(mLightingShaderKey);
	mShaderManagerHandle->setShaderInt(diffuseMat, DIFFUSE_SAMPLE_LOC);
	mShaderManagerHandle->setShaderInt(specularMat, SPECULAR_SAMPLE_LOC);
	mShaderManagerHandle->setShaderFloat(shininess, SHINY_VALUE);
}

void Lighting::initLightingData(int numPointLights)
{
	mShaderManagerHandle->setShaderInt(pointLightNumVar, numPointLights);
}


void Lighting::addDirectionalLight(DirectionalLight *light)
{
	directionalLights.push_back(light);
}

void Lighting::addPointLight(PointLight *light)
{
	pointLights.push_back(light);
	
	int size = pointLights.size();
	light->setUniformIndex(size - 1);
}


void Lighting::addSpotLight(SpotLight *light, Camera* cam)
{
	spotLight = light;
	spotLight->initFlashlight(cam);
}


void Lighting::processLighting(Camera* cam)
{
	mShaderManagerHandle->useShaderByKey(mLightingShaderKey);
	mShaderManagerHandle->setShaderVec3(viewPosition, *cam->getPosition());
	
	//send directional, point, and spotlight data to shader
	RK_Shader* shaderInUse = mShaderManagerHandle->getShaderInUse();

	//directional light data
	for (unsigned int i = 0; i < directionalLights.size(); i++)
		directionalLights[i]->processLightingData(shaderInUse);
	
	//Point light data
	for (unsigned int i = 0; i < pointLights.size(); i++)
		pointLights[i]->processLightingData(shaderInUse);

	//spot light data
	if(spotLight != nullptr)
		spotLight->processLightingData(shaderInUse);
}