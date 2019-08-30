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
			 SpotLight.h
	=========================
	This class handles calculations and values for spot lights and sends them to the fragment shader
	Currently operates as an FPS-style flashlight or a Dark Souls style near-player illumination

********/

#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "Light.h"
#include <RocketMath/Vector3.h>
#include <string>

class RK_Shader;
class Camera;

class SpotLight : Light
{	
	public:
		/*
			* Constructor
		*/
		SpotLight(Vector3 dir, Vector3 amb, Vector3 diff, Vector3 spec, float c, float l, float q, float cut, float outerCut);
		
		/*
			* Calculate light values and send to fragment shader
		*/		
		void processLightingData(RK_Shader* man);

		/*
			* Store a pointer to the player camera
		*/
		void initFlashlight(Camera* cam);
	private:
		std::string positionVar = "spotLight.position", directionVar = "spotLight.direction", cutoffVar = "spotLight.cutOff", 
					outerCutoffVar = "spotLight.outerCutOff", constantVar = "spotLight.constant", linearVar = "spotLight.linear",
					quadraticVar = "spotLight.quadratic";
		std::string ambientVar = "spotLight.ambient", diffuseVar = "spotLight.diffuse", specularVar = "spotLight.specular";


		float constant, linear, quadratic, cutoff, outerCutoff;

		Vector3 position, direction;

		Camera* mpCamHandle;
};

#endif // !SPOT_LIGHT_H
