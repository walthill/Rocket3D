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
			 DirectionalLight.h
	=========================
	This class handles calculations and values for directonal lights and sends them to the fragment shader

********/

#ifndef DIR_LIGHT_H
#define DIR_LIGHT_H

#include "Light.h"
#include <RocketMath/Vector3.h>

class RK_Shader;

class DirectionalLight : Light
{
	public:
		/***
			* Constructor
		***/
		DirectionalLight(Vector3 dir, Vector3 ambient, Vector3 diffuse, Vector3 specular);
		
		/***
			* Empty Deconstructor
		***/
		~DirectionalLight() {};

		/***
			* Calulate light values and send them to the fragment shader
		***/
		void processLightingData(RK_Shader* man);

		/***
			* Set the direction of the light in 3d space
		***/
		void setDirection(Vector3 vec) { mDirection = vec; };
		/***
			* Access the direction of the light in 3d space
		***/
		const Vector3*  getDirection() const { return &mDirection; };
	
	private:
		std::string ambientVar = "dirLight.ambient", diffuseVar = "dirLight.diffuse", specularVar = "dirLight.specular";
		const std::string directionVar = "dirLight.direction";

		Vector3 mDirection;
};

#endif // !DIR_LIGHT_H
