/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 Light.h
	=========================
	This class serves as the base lighting class for all light types

********/

#ifndef LIGHT_H
#define LIGHT_H

#include "../../util/EngineUtils.h"
#include <RocketMath/Vector3.h>

class RK_Shader;

class Light
{
	public:

		/***
			* Constructor
		***/
		Light(Vector3 amb, Vector3 diff, Vector3 spec) 
		{ mAmbientLight = amb; mDiffuseLight = diff; mSpecularLight = spec; };

		/***
			* Pure virtual function that is required in every subclass
		***/
		virtual void processLightingData(RK_Shader* man) PURE_VIRTUAL;

		/***
			* Set ambient light value
		***/
		void setAmbientVector(Vector3 vec) { mAmbientLight = vec; };
		/***
			* Set diffuse light value
		***/
		void setDiffuseVector(Vector3 vec) { mDiffuseLight = vec; };
		/***
			* Set specular light value
		***/
		void setSpecularVector(Vector3 vec) { mSpecularLight = vec; };

		/***
			* Access ambient light value
		***/
		const Vector3*  getAmbientVector() const { return &mAmbientLight; };
		/***
			* Access diffuse light value
		***/
		const Vector3*  getDiffuseVector() const { return &mDiffuseLight; };
		/***
			* Access specular light value
		***/
		const Vector3*  getSpecularVector() const { return &mSpecularLight; };

	protected:
		Vector3 mAmbientLight, mDiffuseLight, mSpecularLight;

	private:
		
};

#endif // !LIGHT_H
