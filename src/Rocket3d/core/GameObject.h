/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
		 GameObject.h
	=========================
	This file contains the definition for the GameObject class.
	The class handles calculations for GameObjects and holds id's 
	for components assigned to the GameObject.

********/

#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <RocketMath/Vector3.h>
#include "../component/Component.h"

class MaterialComponent;
class MeshComponent;
class DirectionalLightComponent;
class PointLightComponent;
class SpotLightComponent;
class TransformComponent;

/***************************************************************************//**
 * @brief 	GameObject class with identifiers for components.
 *
 * This class contains a GameObject's component identifiers and controls the
 * processing of transform data.
 ******************************************************************************/
class GameObject : public Trackable
{
	public:
		///Default constructor
		GameObject();
		///Default deconstructor
		~GameObject();

		///Cleanup
		void destroy();

		/**********************************************************************//**
		* Process transform calulations and send data to Mesh Component.
		*
		* @param elapsedTime Frame timing
		*************************************************************************/
		void update(float elapsedTime);

		///Draw to screen
		void render();

		/**********************************************************************//**
		* Set GameObject's unique id
		*
		* @param id GameObject identifier
		*************************************************************************/
		void setId(uint32 id) { mId = id; }
		
		/**********************************************************************//**
		* Set GameObject's transform reference
		*
		* @param comp TransformComponent reference
		*************************************************************************/
		void setTransformHandle(TransformComponent* comp) { mpTransform = comp; }

		/**********************************************************************//**
		* Set GameObject's transform id
		*
		* @param transfromId Component identifier
		*************************************************************************/
		void connectTransform(ComponentId transfromId) { mTransformId = transfromId; }

		/**********************************************************************//**
		* Set GameObject's mesh id
		*
		* @param meshId MeshComponent identifier
		*************************************************************************/
		void connectMesh(ComponentId meshId) { mMeshId = meshId; }

		/**********************************************************************//**
		* Set GameObject's material id
		*
		* @param materialId Component identifier
		*************************************************************************/
		//void connectMaterial(ComponentId materialId) { mMaterialId = materialId; }

		/**********************************************************************//**
		* Set GameObject's directional light id
		*
		* @param lightId Component identifier
		*************************************************************************/
		void connectDirectionalLight(ComponentId lightId) { mDirectionalLightId = lightId; }

		/**********************************************************************//**
		* Set GameObject's spot light id
		*
		* @param lightId Component identifier
		*************************************************************************/
		void connectSpotLight(ComponentId lightId) { mSpotLightId = lightId; }

		/**********************************************************************//**
		* Set GameObject's point light id
		*
		* @param lightId Component identifier
		*************************************************************************/
		void connectPointLight(ComponentId lightId) { mPointLightId = lightId; }

		///Access the GameObject's id
		uint32 getId() { return mId; }
		///Access the GameObject's transform component id
		ComponentId getTransformId() { return mTransformId; };
		///Access the GameObject's mesh component id
		ComponentId getMeshId() { return mMeshId; };
		///Access the GameObject's material component id
		//ComponentId getMaterialId() { return mMaterialId; };
		///Access the GameObject's spot light component id
		ComponentId getSpotLightId() { return mSpotLightId; }
		///Access the GameObject's directional light component id
		ComponentId getDirectionalLightId() { return mDirectionalLightId; }
		///Access the GameObject's point light component id
		ComponentId getPointLightId() { return mPointLightId; }

		///Acesss the GameObject's transform 
		TransformComponent* getTransform() { return mpTransform; }
		///Acesss the GameObject's mesh 
		MeshComponent* getMesh();
		///Acesss the GameObject's material
		//MaterialComponent* getMaterial();
		///Acesss the GameObject's spot light
		SpotLightComponent* getSpotLight();
		///Acesss the GameObject's directional light
		DirectionalLightComponent* getDirectionalLight();
		///Acesss the GameObject's point light
		PointLightComponent* getPointLight();

	private:
		uint32 mId; //change in GameObjectId
	//	ComponentId mMaterialId;
		ComponentId mMeshId;
		ComponentId mTransformId;

		ComponentId mPointLightId;
		ComponentId mDirectionalLightId;
		ComponentId mSpotLightId;

		TransformComponent* mpTransform;
};

#endif // !GAME_OBJ_H
