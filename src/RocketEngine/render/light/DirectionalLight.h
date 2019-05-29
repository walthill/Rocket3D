#ifndef DIR_LIGHT_H
#define DIR_LIGHT_H

#include "Light.h"
#include <RocketMath/Vector3.h>

class RK_Shader;

class DirectionalLight : Light
{
	public:
		DirectionalLight(Vector3 dir, Vector3 ambient, Vector3 diffuse, Vector3 specular);
		~DirectionalLight() {};

		void processLightingData(RK_Shader* man);

		void setDirection(Vector3 vec) { mDirection = vec; };
		const Vector3*  getDirection() const { return &mDirection; };
	
	private:
		std::string ambientVar = "dirLight.ambient", diffuseVar = "dirLight.diffuse", specularVar = "dirLight.specular";
		const std::string directionVar = "dirLight.direction";

		Vector3 mDirection;
};

#endif // !DIR_LIGHT_H
