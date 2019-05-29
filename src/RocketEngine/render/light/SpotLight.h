#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "Light.h"
#include <RocketMath/Vector3.h>
#include <string>

class RK_Shader;
class Camera;

//CURRENTLY OPERATES AS A FPS FLASHLIGHT

class SpotLight : Light
{	
	public:
		SpotLight(Vector3 dir, Vector3 amb, Vector3 diff, Vector3 spec, float c, float l, float q, float cut, float outerCut);
		void processLightingData(RK_Shader* man);

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
