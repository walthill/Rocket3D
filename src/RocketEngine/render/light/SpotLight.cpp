#include "SpotLight.h"
#include "../../shader/RK_Shader.h"
#include "../Camera.h"

SpotLight::SpotLight(Vector3 dir, Vector3 amb, Vector3 diff, Vector3 spec, float c, float l, float q, float cut, float outerCut)
	:Light(amb, diff, spec),
	direction(dir), cutoff(cut), outerCutoff(outerCut),
	constant(c), linear(l), quadratic(q)
{
	mpCamHandle = nullptr;
}

void SpotLight::initFlashlight(Camera* cam)
{
	mpCamHandle = cam;
}

void SpotLight::processLightingData(RK_Shader * man)
{
	man->setVec3(positionVar, *mpCamHandle->getPosition()); //TODO: throw error here

	man->setVec3(directionVar, *mpCamHandle->getFront());
	man->setFloat(constantVar, constant);
	man->setFloat(linearVar, linear);
	man->setFloat(quadraticVar, quadratic);
	man->setFloat(cutoffVar, cutoff);
	man->setFloat(outerCutoffVar, outerCutoff);

	man->setVec3(ambientVar, mAmbientLight);
	man->setVec3(diffuseVar, mDiffuseLight);
	man->setVec3(specularVar, mSpecularLight);
}
