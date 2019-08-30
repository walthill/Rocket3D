/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This class makes use of tutorials from Learn OpenGL
	(https://learnopengl.com)

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 SpotLight.cpp
	=========================
	
********/
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
	// no need to call use() here as that is called by the lighting class

	man->setVec3(positionVar, *mpCamHandle->getPosition()); 

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
