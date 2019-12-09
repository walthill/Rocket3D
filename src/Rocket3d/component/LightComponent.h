#ifndef POINT_LIGHT_COMPONENT_H
#define POINT_LIGHT_COMPONENT_H

#include <RocketMath/Vector3.h>
#include "Component.h"

struct BaseLightData
{
	Vector3 ambientLight, diffuseLight, specularLight;

	BaseLightData() : ambientLight(Vector3::zero), diffuseLight(Vector3::zero), specularLight(Vector3::zero) {};
	BaseLightData(Vector3 ambient, Vector3 diffuse, Vector3 specular) :
		ambientLight(ambient), diffuseLight(diffuse), specularLight(specular) {};
};

/******************************************************************

	POINT LIGHT
	Shader allows for multiple point lights

*****************************************************************/

struct PointLightData
{
	//Base lighting data
	BaseLightData mBaseLightData;
	//Point-light specific data
	Vector3 mPosition;
	float mConstant, mLinear, mQuadratic;

	PointLightData() : mBaseLightData(), mPosition(Vector3::zero), mConstant(0), mLinear(0), mQuadratic(0) {}
	PointLightData(BaseLightData data, Vector3 pos, float constant, float linear, float quadratic) : 
		mBaseLightData(data), mPosition(pos), mConstant(constant), mLinear(linear), mQuadratic(quadratic) {}
};

const PointLightData ZERO_POINT_LIGHT_DATA;

class RK_Shader;

class PointLightComponent : public Component
{
	public:
		PointLightComponent(const ComponentId& id);
		~PointLightComponent();

		void processLightingData(RK_Shader* lightingShader);

		PointLightData* getData() { return &mPointLightData; }

		void setData(const PointLightData& data) { mPointLightData = data; }
		void setUniformIndex(int ind);
	
	private:
		//Variables for passing data to uniforms
		std::string positionVar = "position", constantVar = "constant", linearVar = "linear", quadraticVar = "quadratic";
		std::string ambientVar = "ambient", diffuseVar = "diffuse", specularVar = "specular";
		
		std::string varIndex;
		int indexInPointLightList;

		PointLightData mPointLightData;
};

/*****************************************************************
	DIRECTIONAL LIGHT

	Shader allows for one directional light

*****************************************************************/


struct DirectionalLightData
{
	//Base lighting data
	BaseLightData mBaseLightData;

	//Directional light specific data
	Vector3 mDirection;

	DirectionalLightData() : mBaseLightData(), mDirection(Vector3::zero) {}
	DirectionalLightData(BaseLightData data, Vector3 dir) : mBaseLightData(data), mDirection(dir) {}
};

const DirectionalLightData ZERO_DIRECTIONAL_LIGHT_DATA;

class DirectionalLightComponent : public Component
{
	public:
		DirectionalLightComponent(const ComponentId& id);
		~DirectionalLightComponent();

		void processLightingData(RK_Shader* lightingShader);

		DirectionalLightData* getData() { return &mDirLightData; }
		void setData(const DirectionalLightData& data) { mDirLightData = data; }

	private:
		//Variables for passing data to uniforms
		const std::string ambientVar = "dirLight.ambient", diffuseVar = "dirLight.diffuse", specularVar = "dirLight.specular";
		const std::string directionVar = "dirLight.direction";

		DirectionalLightData mDirLightData;
};



/*****************************************************************
	SPOTLIGHT
	
	Shader allows for one spotlight (see below)

	NOTE: The spotlight is currently meant to be used on the player camera

*****************************************************************/


struct SpotLightData
{
	//Base lighting data
	BaseLightData mBaseLightData;

	//Directional light specific data
	Vector3 mDirection, mPosition;
	float mConstant, mLinear, mQuadratic, mCutoff, mOuterCutoff;
	
	SpotLightData() : 
		mBaseLightData(), mDirection(Vector3::zero), mPosition(Vector3::zero), mConstant(0), mLinear(0), mQuadratic(0),
		mCutoff(0), mOuterCutoff(0){}


	SpotLightData(BaseLightData data, Vector3 dir, Vector3 pos, float constant, float linear, float quadratic, float cutoff, float outerCuttoff) :
		mBaseLightData(), mDirection(Vector3::zero), mPosition(pos), mConstant(constant), mLinear(linear), mQuadratic(quadratic),
		mCutoff(cutoff), mOuterCutoff(outerCuttoff) {}
};

const SpotLightData ZERO_SPOTLIGHT_DATA;

class SpotLightComponent : public Component
{
	public:
		SpotLightComponent(const ComponentId& id);
		~SpotLightComponent();

		void processLightingData(RK_Shader* lightingShader);

		SpotLightData* getData() { return &mSpotlightData; }
		void setData(const SpotLightData& data) { mSpotlightData = data; }

	private:
		//Variables for passing data to uniforms
		const std::string positionVar = "spotLight.position", directionVar = "spotLight.direction", cutoffVar = "spotLight.cutOff",
					outerCutoffVar = "spotLight.outerCutOff", constantVar = "spotLight.constant", linearVar = "spotLight.linear",
					quadraticVar = "spotLight.quadratic";
		const std::string ambientVar = "spotLight.ambient", diffuseVar = "spotLight.diffuse", specularVar = "spotLight.specular";

		SpotLightData mSpotlightData;
};


#endif //!POINT_LIGHT_COMPONENT_H