#ifndef LIGHTING_H
#define LIGHTING_H

#include "../../util/EngineUtils.h"

class ShaderManager;
class Camera;
class DirectionalLight;
class PointLight;
class SpotLight;

enum LightType { DIR_LIGHT , POINT_LIGHT, SPOT_LIGHT };

class Lighting //Used to init lighting shader variables
{
	public:
		Lighting(ShaderKey key, ShaderManager* man);
		//TODO: cleanup pointers
		void initialize(ShaderKey lightingShader, ShaderManager* man);
		
		void processLighting(Camera* cam);

		void addLight(DirectionalLight* light);
		void addLight(PointLight* light);
		void addLight(SpotLight* light, Camera* cam);

	private:
		// uniform names
		const std::string diffuseMat = "material.diffuse", specularMat = "material.specular", shininess = "material.shininess";		
		const std::string viewPosition = "viewPos", pointLightNumVar = "numPointLights";


		const int DIFFUSE_SAMPLE_LOC = 0, SPECULAR_SAMPLE_LOC = 1;
		const float SHINY_VALUE = 32.0f; //32, 64, 128 , etc...

		ShaderManager* mShaderManagerHandle;
		ShaderKey mLightingShaderKey;

		std::vector<DirectionalLight*> directionalLights;
		std::vector<PointLight*> pointLights;
		SpotLight* spotLight; //flashlight

		void initMaterialData();
		void initLightingData(int numPointLights);
};

#endif // !LIGHT_H
