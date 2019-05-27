#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"
#include <string>

class RK_Shader;

class PointLight : Light
{
	public:
		PointLight(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular, float constant, float linear, float quadratic);
		void processLightingData(RK_Shader* man);

		void setIndex(int ind) 
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

	private:
		std::string positionVar = "position", constantVar = "constant", linearVar = "linear", quadraticVar = "quadratic";
		std::string ambientVar = "ambient", diffuseVar = "diffuse", specularVar = "specular";
		std::string varIndex;// = "pointLights[ " + std::to_string(indexInPointLightList) + "].";
		
		Vector3 position;
		float constant, linear, quadratic;
		int indexInPointLightList;
};

#endif // !POINT_LIGHT_H
