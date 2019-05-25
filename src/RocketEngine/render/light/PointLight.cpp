#include "PointLight.h"
#include "../../shader/RK_Shader.h"

PointLight::PointLight(Vector3 pos, Vector3 amb, Vector3 diff, Vector3 spec, float c, float l, float q)
	:Light(amb, diff, spec),
	position(pos), constant(c), linear(l), quadratic(q)
{
}

void PointLight::processLightingData(RK_Shader * man)
{
	man->setVec3(positionVar, position);
	man->setFloat(constantVar, constant);
	man->setFloat(linearVar, linear);
	man->setFloat(quadraticVar, quadratic);

	man->setVec3(ambientVar, mAmbientLight);
	man->setVec3(diffuseVar, mDiffuseLight);
	man->setVec3(specularVar, mSpecularLight);
/*	// point light 1
	mpShaderManager->setShaderVec3("pointLights[0].position", pointLightPositions[0]);
	mpShaderManager->setShaderVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	mpShaderManager->setShaderVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	mpShaderManager->setShaderVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	mpShaderManager->setShaderFloat("pointLights[0].constant", 1.0f);
	mpShaderManager->setShaderFloat("pointLights[0].linear", 0.09);
	mpShaderManager->setShaderFloat("pointLights[0].quadratic", 0.032);*/
}
