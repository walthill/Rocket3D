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
			 PointLight.cpp
	=========================

********/

#include "PointLight.h"
#include "../../shader/RK_Shader.h"

PointLight::PointLight(Vector3 pos, Vector3 amb, Vector3 diff, Vector3 spec, float c, float l, float q)
	:Light(amb, diff, spec),
	position(pos), constant(c), linear(l), quadratic(q)
{
}

void PointLight::processLightingData(RK_Shader * man)
{
	// no need to call use() here as that is called by the lighting class

	man->setVec3(positionVar, position);
	man->setFloat(constantVar, constant);
	man->setFloat(linearVar, linear);
	man->setFloat(quadraticVar, quadratic);

	man->setVec3(ambientVar, mAmbientLight);
	man->setVec3(diffuseVar, mDiffuseLight);
	man->setVec3(specularVar, mSpecularLight);
}

void PointLight::setUniformIndex(int ind)
{
	indexInPointLightList = ind;
	varIndex = "pointLights[" + std::to_string(indexInPointLightList) + "].";
	positionVar = varIndex + positionVar;
	constantVar = varIndex + constantVar;
	linearVar = varIndex + linearVar;
	quadraticVar = varIndex + quadraticVar;

	ambientVar = varIndex + ambientVar;
	diffuseVar = varIndex + diffuseVar;
	specularVar = varIndex + specularVar;
};