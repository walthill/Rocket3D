#include "Lighting.h"
#include "../../shader/ShaderManager.h"
#include "../Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

Lighting::Lighting(ShaderKey key, ShaderManager* man)
{
	mLightingShaderKey = key;
	mShaderManagerHandle = man;
	initMaterialData();
}

void Lighting::initialize(ShaderKey key, ShaderManager* man)
{
	mLightingShaderKey = key;
	mShaderManagerHandle = man;
	initMaterialData();
};

void Lighting::initMaterialData()
{
	mShaderManagerHandle->useShaderByKey(mLightingShaderKey);
	mShaderManagerHandle->setShaderInt(diffuseMat, DIFFUSE_SAMPLE_LOC);
	mShaderManagerHandle->setShaderInt(specularMat, SPECULAR_SAMPLE_LOC);
	mShaderManagerHandle->setShaderFloat(shininess, SHINY_VALUE);
}



void Lighting::addLight(DirectionalLight *light)
{
		DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(light);
		directionalLights.push_back(dirLight);
}

void Lighting::addLight(PointLight *light)
{
	PointLight* pointLight = dynamic_cast<PointLight*>(light);
	pointLights.push_back(pointLight);
}


void Lighting::addLight(SpotLight *light)
{
	SpotLight* spotLight = dynamic_cast<SpotLight*>(light);
	spotLights.push_back(spotLight);
}


void Lighting::processLighting(Camera* cam)
{
	mShaderManagerHandle->useShaderByKey(mLightingShaderKey);
	mShaderManagerHandle->setShaderVec3(viewPosition, cam->getPosition());
	
	//send directional, point, and spotlight data to shader
	RK_Shader* shaderInUse = mShaderManagerHandle->getShaderInUse();

	//directional light data
	for (unsigned int i = 0; i < directionalLights.size(); i++)
		directionalLights[i]->processLightingData(shaderInUse);
	
	//Point light data
	for (unsigned int i = 0; i < pointLights.size(); i++)
		pointLights[i]->processLightingData(shaderInUse);

	//spot light data
	for (unsigned int i = 0; i < spotLights.size(); i++)
		spotLights[i]->processLightingData(shaderInUse);
}