/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
		 ComponentManager.h
	=========================
	This file contains the definition for the ComponentManager class.
	The class handles calculations and rendering for components 
	and holds all components allocated to GameObjects.

********/

#ifndef COMPONENT_MAN_H
#define COMPONENT_MAN_H

#include <map>
#include <rkutil/DeanLib_MemoryPool.h>
//#include "MaterialComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "LightComponent.h"


class ShaderManager;
/***************************************************************************//**
 * @brief 	Stores collection of components.
 *
 * Stores collection of components. and handles their processing and rendering
 ******************************************************************************/
class ComponentManager : public rkutil::Trackable
{
	public:
		/**********************************************************************//**
		* Process components and perform calulations.
		*
		* @param maxSize Sets maximum number of components
		* @param shaderMan Refernce to the shader manager
		* @param lightingShaderKey Identifier for the shader used in lighting components
		*************************************************************************/
		ComponentManager(uint32 maxSize, ShaderManager* shaderMan, ShaderKey lightingShaderKey);

		///Default decconstructor
		~ComponentManager();

		///Cleanup
		void clean();

		//TRANSFORM

		/**********************************************************************//**
		* Access the transform component based on the component identifier.
		*
		* @param id Component identifier
		*************************************************************************/
		TransformComponent* getTransformComponent(const ComponentId& id);

		/**********************************************************************//**
		* Create transform component based on data passed in and return the component identifier.
		*
		* @param data data Transform component data
		*************************************************************************/
		ComponentId allocateTransformComponent(const TransformData& data = ZERO_TRANSFORM_DATA);

		/**********************************************************************//**
		* Remove and destroy transform component from the collection based on the component identifier.
		* 
		* @param id Component identifier
		*************************************************************************/
		void deallocateTransformComponent(const ComponentId& id);

		//MESH
		/**********************************************************************//**
		* Access the mesh component based on its component identifier.
		*
		* @param id Component identifier
		*************************************************************************/
		MeshComponent* getMeshComponent(const ComponentId& id);

		/**********************************************************************//**
		* Create mesh component based on data passed in and return the component identifier.
		*
		* @param meshId mesh component identifier
		* @param data data Mesh component data
		*************************************************************************/
		ComponentId allocateMeshComponent(const ComponentId& meshId, const	MeshComponentData& data = ZERO_MESH_DATA);

		/**********************************************************************//**
		* Remove and destroy mesh component from the collection based on the component identifier.
		*
		* @param id Component identifier
		*************************************************************************/
		void deallocateMeshComponent(const ComponentId& id);

		//DIRECTIONAL LIGHT
		/**********************************************************************//**
		* Access a reference to a directional light component based on its component identifier.
		*
		* @param id Component identifier
		*************************************************************************/
		DirectionalLightComponent* getDirectionalLightComponent(const ComponentId& id);

		/**********************************************************************//**
		* Create directional light component based on data passed in and return the component identifier.
		*
		* @param dirLightId
		* @param data data Directional Light component data
		*************************************************************************/
		ComponentId allocateDirectionalLightComponent(const ComponentId& dirLightId, const DirectionalLightData& data = ZERO_DIRECTIONAL_LIGHT_DATA);

		/**********************************************************************//**
		* Remove and destroy directional light component from the collection based on the component identifier.
		*
		* @param id Component identifier
		*************************************************************************/
		void deallocateDirectionalLightComponent(const ComponentId& id);


		//POINT LIGHT
		/**********************************************************************//**
		* Access a reference to a point light component based on its component identifier.
		*
		* @param id Component identifier
		*************************************************************************/

		PointLightComponent* getPointLightComponent(const ComponentId& id);
		/**********************************************************************//**
		* Create mesh component based on data passed in and return the component identifier.
		*
		* @param pointLighId
		* @param data data Point Light component data
		*************************************************************************/
		ComponentId allocatePointLightComponent(const ComponentId& pointLightId, const PointLightData& data = ZERO_POINT_LIGHT_DATA);

		/**********************************************************************//**
		* Remove and destroy point light component from the collection based on the component identifier.
		*
		* @param id Component identifier
		*************************************************************************/
		void deallocatePointLightComponent(const ComponentId& id);

		//SPOT LIGHT
		/**********************************************************************//**
		* Access a reference to a spot light component based on its component identifier.
		*
		* @param id Component identifier
		*************************************************************************/
		SpotLightComponent* getSpotlightComponent(const ComponentId& id);
		
		/**********************************************************************//**
		* Create Spot Light component based on data passed in and return the component identifier.
		*
		* @param meshId
		* @param data data Spot Light component data
		*************************************************************************/
		ComponentId allocateSpotlightComponent(const ComponentId& spotlightId, const	SpotLightData& data = ZERO_SPOTLIGHT_DATA);

		/**********************************************************************//**
		* Remove and destroy spot light component from the collection based on the component identifier.
		*
		* @param id Component identifier
		*************************************************************************/
		void deallocateSpotlightComponent(const ComponentId& id);

		/**********************************************************************//**
		* Process components and perform calulations.
		*
		* @param elapsedTime Frame timing
		*************************************************************************/
		void update(float elapsedTime);

		///Send light component data to shader
		void processLightingComponents();
		///Draw model meshes to screen
		void renderMeshes();

		///Get number of Mesh Components
		int getNumberOfMeshes() { return mMeshComponentMap.size(); }
		///Get number of Transform Components
		int getNumberOfTransforms() { return mTransformComponentMap.size(); }
		///Get number of Point Light Components
		int getNumberOfPointLights() { return mPointLightComponentMap.size(); }
		///Get number of Spot Light Components
		int getNumberOfSpotlights() { return mSpotlightComponentMap.size(); }
		///Get number of Directional Light Components
		int getNumberOfDirectionalLights() { return mDirectionalLightComponentMap.size(); }
	private:
		const std::string pointLightNumVar = "numPointLights";
		ShaderManager* mpShaderManagerHandle;
		ShaderKey mLightingShaderKey;

		rkutil::MemoryPool mTransformPool;
		rkutil::MemoryPool mMeshPool;
		rkutil::MemoryPool mDirectionalLightPool;
		rkutil::MemoryPool mPointLightPool;
		rkutil::MemoryPool mSpotlightPool;

		std::map<ComponentId, TransformComponent*> mTransformComponentMap;
		std::map<ComponentId, MeshComponent*> mMeshComponentMap;
		std::map<ComponentId, PointLightComponent*> mPointLightComponentMap;
		std::map<ComponentId, DirectionalLightComponent*> mDirectionalLightComponentMap;
		std::map<ComponentId, SpotLightComponent*> mSpotlightComponentMap;

		static ComponentId msNextTransformComponentId;
		static ComponentId msNextMeshComponentId;
		static ComponentId msNextMaterialComponentId;
		static ComponentId msNextPointLightComponentId;
		static ComponentId msNextDirectionalLightComponentId;
		static ComponentId msNextSpotlightComponentId;
};

#endif // !COMPONENT_MAN_H
