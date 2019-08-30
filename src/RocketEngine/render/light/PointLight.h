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
			 PointLight.h
	=========================
	This class handles calculations and values for point lights and sends them to the fragment shader

********/

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"
#include <string>

class RK_Shader;

class PointLight : Light
{
	public:
		/***
			* Constructor
		***/
		PointLight(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular, 
					float constant, float linear, float quadratic);
		/***
			* Calculate point light values
		***/
		void processLightingData(RK_Shader* man);

		/***
			* Set uniform index values to be sent to the fragment shader
		***/
		void setUniformIndex(int ind);

	private:
		std::string positionVar = "position", constantVar = "constant", linearVar = "linear", quadraticVar = "quadratic";
		std::string ambientVar = "ambient", diffuseVar = "diffuse", specularVar = "specular";
		std::string varIndex;
		
		Vector3 position;
		float constant, linear, quadratic;
		int indexInPointLightList;
};

#endif // !POINT_LIGHT_H
