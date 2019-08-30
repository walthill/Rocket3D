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
			 DirectionalLight.cpp
	=========================

********/

#include "DirectionalLight.h"
#include "../../shader/RK_Shader.h"

DirectionalLight::DirectionalLight(Vector3 dir, Vector3 ambient, Vector3 diff, Vector3 spec)
	:Light(ambient, diff, spec), mDirection(dir)
{
}

void DirectionalLight::processLightingData(RK_Shader* shader) 
{
	// send directional light data to shader/gpu
	// no need to call use() here as that is called by the lighting class

	shader->setVec3(directionVar, mDirection);

	shader->setVec3(ambientVar, mAmbientLight);
	shader->setVec3(diffuseVar, mDiffuseLight);
	shader->setVec3(specularVar, mSpecularLight);

}
