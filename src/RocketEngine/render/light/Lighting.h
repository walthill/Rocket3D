/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 Lighting.h
	=========================
	This class serves as a manager for all light types. 
	It contains calls to add lights and calls for lights perform their calculations
********/

#ifndef LIGHTING_H
#define LIGHTING_H

#include "../../util/EngineUtils.h"

class ShaderManager;
class Camera;
class DirectionalLight;
class PointLight;
class SpotLight;

//enum LightType { DIR_LIGHT , POINT_LIGHT, SPOT_LIGHT };

class Lighting : public rkutil::Trackable //Used to init lighting shader variables
{
	public:
		/***
			* Constructor takes a pointer to the general lighting shader
		***/
		Lighting(ShaderKey key, ShaderManager* man, int numberOfPointLights = 0);
		
		/***
			* Deconstructor calls clean
		***/
		~Lighting();

		/***
			* Initialize lighting settings on the shader and set the number of point lights in the scene
		***/
		void initialize(ShaderKey lightingShader, ShaderManager* man, int numberOfPointLights = 0);

		/***
			* Cleans memory
		***/
		void clean();

		/***
			* Makes function calls to each light source to perform its calculations
		***/
		void processLighting(Camera* cam);

		/***
			* Add a directional light to the vector
		***/
		void addDirectionalLight(DirectionalLight* light);

		/***
			* Add a point light to the vector
		***/
		void addPointLight(PointLight* light);

		/***
			* Add a spot light to the vector
		***/
		void addSpotLight(SpotLight* light, Camera* cam);

	private:
		// uniform names
		const std::string diffuseMat = "material.diffuse", specularMat = "material.specular", shininess = "material.shininess";		
		const std::string viewPosition = "viewPos", pointLightNumVar = "numPointLights";


		const int DIFFUSE_SAMPLE_LOC = 0, SPECULAR_SAMPLE_LOC = 1;
		const float SHINY_VALUE = 32.0f; //32, 64, 128 , etc...

		ShaderManager* mShaderManagerHandle;
		ShaderKey mLightingShaderKey;

		std::vector<DirectionalLight*> mpDirectionalLights;
		std::vector<PointLight*> mpPointLights;
		SpotLight* mpSpotLight; //flashlight

		void initMaterialData();
		void initLightingData(int numPointLights);
};

#endif // !LIGHT_H
