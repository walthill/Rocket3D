/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
		LightComponent.h
	=========================
	This file contains all lighting components and their class definitions.

********/

#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include <RocketMath/Vector3.h>
#include "Component.h"

/***************************************************************************//**
 * @brief 	Data used in every lighting component.
 *
 * This struct contains data and constructors that will serve as foundational data 
 * for every light component's data
 ******************************************************************************/
struct BaseLightData
{
	Vector3 ambientLight; ///< Ambient light value
	Vector3 diffuseLight; ///< Diffuse light value
	Vector3 specularLight; ///< Specular light value

	///Default constructor sets all values to zero
	BaseLightData() : ambientLight(Vector3::zero), diffuseLight(Vector3::zero), specularLight(Vector3::zero) {};

	///Constructor that takes in values for struct variables
	BaseLightData(Vector3 ambient, Vector3 diffuse, Vector3 specular) :
		ambientLight(ambient), diffuseLight(diffuse), specularLight(specular) {};
};

/******************************************************************

	POINT LIGHT
	Shader allows for multiple point lights

*****************************************************************/

/***************************************************************************//**
 * @brief 	Data used in every Point Light component.
 *
 * This struct contains data and constructors that are used to calculate 
 * and render Point Lights
 ******************************************************************************/
struct PointLightData
{
	BaseLightData mBaseLightData; ///< Base lighting data
	//Point-light specific data
	Vector3 mPosition;			///< Point light world position value
	//Values for light intensity, smoothness, and falloff 
	//TODO: (review notes to make more detailed comments on lighting variables)
	float mConstant, mLinear, mQuadratic;

	///Default constructor sets all values to zero
	PointLightData() : mBaseLightData(), mPosition(Vector3::zero), mConstant(0), mLinear(0), mQuadratic(0) {}

	///Constructor that takes in values for struct variables
	PointLightData(BaseLightData data, Vector3 pos, float constant, float linear, float quadratic) : 
		mBaseLightData(data), mPosition(pos), mConstant(constant), mLinear(linear), mQuadratic(quadratic) {}
};

const PointLightData ZERO_POINT_LIGHT_DATA;

class RK_Shader;

/***************************************************************************//**
 * @brief 	The component for Point Lights.
 *
 * This class, derived from Component, contains data and uniform names 
 * needed to render point lights.
 ******************************************************************************/
class PointLightComponent : public Component
{
	public:

		/**********************************************************************//**
		 * Creates component with the given id value.
		 *
		 * @param id ComponentId value assigned to this instance of the Component class
		 *************************************************************************/
		PointLightComponent(const ComponentId& id);
		
		///Point Light destructor
		~PointLightComponent();

		/**********************************************************************//**
		 * Send lighting data to the shader through unifroms
		 *
		 * @param lightingShader Reference to the shader to recieve uniform data
		 *************************************************************************/
		void processLightingData(RK_Shader* lightingShader);


		///Access Point Light data from the component
		PointLightData* getData() { return &mPointLightData; }

		/**********************************************************************//**
		 * Set lighting data 
		 *
		 * @param data PointLightData struct with lighting data to store in the component
		 *************************************************************************/
		void setData(const PointLightData& data) { mPointLightData = data; }

		/**********************************************************************//**
		 * Set the names of uniform variables 
		 *
		 * @param index The index for this Point Light in the array of Point Lights in the shader
		 *************************************************************************/
		void setUniformIndex(int index);
	
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

/***************************************************************************//**
 * @brief 	Data used in every Directional Light component.
 *
 * This struct contains data and constructors that are used to calculate
 * and render Directional Lights
 ******************************************************************************/
struct DirectionalLightData
{
	BaseLightData mBaseLightData; ///< Base lighting data

	//Directional light specific data
	Vector3 mDirection;			 ///< Light direction value

	///Default constructor
	DirectionalLightData() : mBaseLightData(), mDirection(Vector3::zero) {}

	///Constructor that takes in values for struct variables
	DirectionalLightData(BaseLightData data, Vector3 dir) : mBaseLightData(data), mDirection(dir) {}
};

const DirectionalLightData ZERO_DIRECTIONAL_LIGHT_DATA;

/***************************************************************************//**
 * @brief 	The component for Directional Lights.
 *
 * This class, derived from Component, contains data and uniform names needed to render 
 * directional lights.
 ******************************************************************************/
class DirectionalLightComponent : public Component
{
	public:

		/**********************************************************************//**
		 * Creates component with the given id value.
		 *
		 * @param id ComponentId value assigned to this instance of the Component class
		 *************************************************************************/
		DirectionalLightComponent(const ComponentId& id);

		///Point Light destructor
		~DirectionalLightComponent();

		/**********************************************************************//**
		 * Send lighting data to the shader through unifroms
		 *
		 * @param lightingShader Reference to the shader to recieve uniform data
		 *************************************************************************/
		void processLightingData(RK_Shader* lightingShader);

		///Access Directional Light data from the component
		DirectionalLightData* getData() { return &mDirLightData; }

		/**********************************************************************//**
		 * Set lighting data
		 *
		 * @param data DirectionalLightData struct with lighting data to store in the component
		 *************************************************************************/
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
class Camera;

/***************************************************************************//**
 * @brief 	Data used in every Spot Light component.
 *
 * This struct contains data and constructors that are used to calculate
 * and render Spot Lights
 ******************************************************************************/
struct SpotLightData
{
	BaseLightData mBaseLightData; ///< Base lighting data

	//Directional light specific data
	Camera* mpCamHandle;		 ///< Refernce to the player camera

	//Values for light intensity, smoothness, and falloff 
	//TODO: (review notes to make more detailed comments on lighting variables)
	float mConstant, mLinear, mQuadratic, mCutoff, mOuterCutoff;
	
	///Default constructor sets all values to null or zero
	SpotLightData() : 
		mBaseLightData(), mpCamHandle(nullptr), mConstant(0), mLinear(0), mQuadratic(0),
		mCutoff(0), mOuterCutoff(0){}

	///Constructor that takes in values for struct variables
	SpotLightData(BaseLightData data, Camera* cam, Vector3 dir, Vector3 pos, float constant, float linear, float quadratic, float cutoff, float outerCuttoff) :
		mBaseLightData(), mpCamHandle(cam), mConstant(constant), mLinear(linear), mQuadratic(quadratic),
		mCutoff(cutoff), mOuterCutoff(outerCuttoff) {}
};

const SpotLightData ZERO_SPOTLIGHT_DATA;

/***************************************************************************//**
 * @brief 	The component for Spot Lights.
 *
 * This class, derived from Component, contains data and uniform names
 * needed to render spot lights.
 ******************************************************************************/
class SpotLightComponent : public Component
{
	public:
		/**********************************************************************//**
		 * Creates component with the given id value.
		 *
		 * @param id ComponentId value assigned to this instance of the Component class
		 *************************************************************************/
		SpotLightComponent(const ComponentId& id);

		///Point Light destructor
		~SpotLightComponent();

		/**********************************************************************//**
		* Send lighting data to the shader through unifroms
		*
		* @param lightingShader Reference to the shader to recieve uniform data
		*************************************************************************/
		void processLightingData(RK_Shader* lightingShader);

		///Access Spot Light data from the component
		SpotLightData* getData() { return &mSpotlightData; }

		/**********************************************************************//**
		* Set lighting data
		*
		* @param data SpotLightData struct with lighting data to store in the component
		*************************************************************************/
		void setData(const SpotLightData& data) { mSpotlightData = data; }

	private:
		//Variables for passing data to uniforms
		const std::string positionVar = "spotLight.position", directionVar = "spotLight.direction", cutoffVar = "spotLight.cutOff",
					outerCutoffVar = "spotLight.outerCutOff", constantVar = "spotLight.constant", linearVar = "spotLight.linear",
					quadraticVar = "spotLight.quadratic";
		const std::string ambientVar = "spotLight.ambient", diffuseVar = "spotLight.diffuse", specularVar = "spotLight.specular";

		SpotLightData mSpotlightData;
};


#endif //!LIGHT_COMPONENT_H