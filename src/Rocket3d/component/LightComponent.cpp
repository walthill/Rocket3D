#include "LightComponent.h"

#include "../../RocketEngine/shader/RK_Shader.h"


/*****************************************************************
	
	POINT LIGHT

*****************************************************************/

PointLightComponent::PointLightComponent(const ComponentId& id) : 
	Component(id)
{
}

PointLightComponent::~PointLightComponent()
{
}

void PointLightComponent::processLightingData(RK_Shader* lightingShader)
{
	//Point light uniforms
	lightingShader->setVec3(positionVar, mPointLightData.mPosition);
	lightingShader->setFloat(constantVar, mPointLightData.mConstant);
	lightingShader->setFloat(linearVar, mPointLightData.mLinear);
	lightingShader->setFloat(quadraticVar, mPointLightData.mQuadratic);

	//Base lighting uniforms
	lightingShader->setVec3(ambientVar, mPointLightData.mBaseLightData.ambientLight);
	lightingShader->setVec3(diffuseVar, mPointLightData.mBaseLightData.diffuseLight);
	lightingShader->setVec3(specularVar, mPointLightData.mBaseLightData.specularLight);
}

void PointLightComponent::setUniformIndex(int index)
{
	indexInPointLightList = index;
	varIndex = "pointLights[" + std::to_string(indexInPointLightList) + "].";
	positionVar = varIndex + positionVar;
	constantVar = varIndex + constantVar;
	linearVar = varIndex + linearVar;
	quadraticVar = varIndex + quadraticVar;

	ambientVar = varIndex + ambientVar;
	diffuseVar = varIndex + diffuseVar;
	specularVar = varIndex + specularVar;
}


/*****************************************************************
	
	DIRECTIONAL LIGHT

*****************************************************************/


DirectionalLightComponent::DirectionalLightComponent(const ComponentId& id) :
	Component(id)
{
}

DirectionalLightComponent::~DirectionalLightComponent()
{
}

void DirectionalLightComponent::processLightingData(RK_Shader* lightingShader)
{
	// send directional light data to shader/gpu
	// no need to call use() here as that is called by the lighting class

	lightingShader->setVec3(directionVar, mDirLightData.mDirection);

	//Base lighting uniforms
	lightingShader->setVec3(ambientVar, mDirLightData.mBaseLightData.ambientLight);
	lightingShader->setVec3(diffuseVar, mDirLightData.mBaseLightData.diffuseLight);
	lightingShader->setVec3(specularVar, mDirLightData.mBaseLightData.specularLight);

}

/*****************************************************************

	SPOTLIGHT
	NOTE: The spotlight is currently tied to the player camera

*****************************************************************/

SpotLightComponent::SpotLightComponent(const ComponentId& id) :
	Component(id)
{
}

SpotLightComponent::~SpotLightComponent()
{
}

void SpotLightComponent::processLightingData(RK_Shader* lightingShader)
{
	lightingShader->setVec3(positionVar, mSpotlightData.mPosition);
	lightingShader->setVec3(directionVar, mSpotlightData.mDirection);

	lightingShader->setFloat(constantVar, mSpotlightData.mConstant);
	lightingShader->setFloat(linearVar, mSpotlightData.mLinear);
	lightingShader->setFloat(quadraticVar, mSpotlightData.mQuadratic);
	lightingShader->setFloat(cutoffVar, mSpotlightData.mCutoff);
	lightingShader->setFloat(outerCutoffVar, mSpotlightData.mOuterCutoff);

	//Base lighting uniforms
	lightingShader->setVec3(ambientVar, mSpotlightData.mBaseLightData.ambientLight);
	lightingShader->setVec3(diffuseVar, mSpotlightData.mBaseLightData.diffuseLight);
	lightingShader->setVec3(specularVar, mSpotlightData.mBaseLightData.specularLight);
}
