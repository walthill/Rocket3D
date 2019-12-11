/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
		 GameObjectManager.h
	=========================
	This file contains the definition for the GameObject Manager class.
	The class handles calculations and rendering for all GameObjects
********/

#ifndef GAME_OBJ_MAN_H
#define GAME_OBJ_MAN_H

#include <vector>
#include <map>
#include "../../RocketEngine/util/EngineUtils.h"
#include <DeanLib/MemoryPool.h>
#include "GameObject.h"
#include "../component/TransformComponent.h"
#include "../component/MeshComponent.h"
#include "../component/MaterialComponent.h"
#include "../component/LightComponent.h"

class ComponentManager;

typedef uint32 GameObjectId;

const GameObjectId PLAYER_OBJ_ID = 0;
const uint32 INVALID_GAMEOBJECT_ID = UINT_MAX;


/***************************************************************************//**
 * @brief 	The manager for all GameObjects.
 *
 * This class, contains all GameObjects and controls their 
 * rendering, processing, creation, and deletion.
 ******************************************************************************/
class GameObjectManager : public Trackable
{
	public:

		/**********************************************************************//**
		* Constructor for the manager.
		*
		* @param maxSize Sets the max number of GameObjects
		*************************************************************************/
		GameObjectManager(uint32 maxSize);

		///Default deconstructor
		~GameObjectManager();		

		/**********************************************************************//**
		* Find and return a reference to a GameObject based on its id
		*
		* @param id The unique identifier for the GameObject to find
		*************************************************************************/
		GameObject* findGameObject(const GameObjectId& id) const;
		

		/**********************************************************************//**
		* Create a gameObject and return a referecne to that object.
		*
		* @param transform Data for the GameObject's transform. Defaults to a transform with posiion (0,0,0). 
		* @param meshData Data for the GameObject's model. Defaults to a empty MeshComponent.
		* @param id The identifier for the GameObject. Defaults to an invalid value and is assigned in the function
		*************************************************************************/
		GameObject* createGameObject(const TransformData& transform = ZERO_TRANSFORM_DATA,
									const MeshComponentData& meshData = ZERO_MESH_DATA, 
									/*const MaterialData& matData = ZERO_MAT_DATA, */
									const GameObjectId& id = INVALID_GAMEOBJECT_ID);

		/**********************************************************************//**
		* Destroy GameObject and remove from manager based on its id
		*
		* @param id The unique identifier for the GameObject to destroy
		*************************************************************************/
		void destroy(const GameObjectId& id);

		/**********************************************************************//**
		* Create point light and assign to GameObject based on the given id
		*
		* @param id The unique identifier for the GameObject to connect with the new light component
		* @param pointLightData Data for creating a point light component
		*************************************************************************/
		void addPointLight(const GameObjectId& id, const PointLightData& pointLightData);
		
		/**********************************************************************//**
		* Create directional light and assign to GameObject based on the given id
		*
		* @param id The unique identifier for the GameObject to connect with the new light component
		* @param dirLightData Data for creating a directional light component
		*************************************************************************/
		void addDirectionalLight(const GameObjectId& id, const DirectionalLightData& dirLightData);
		
		/**********************************************************************//**
		* Create spot light and assign to GameObject based on the given id
		*
		* @param id The unique identifier for the GameObject to connect with the new light component
		* @param spotLightData Data for creating a spot light component
		*************************************************************************/
		void addSpotLight(const GameObjectId& id, const SpotLightData& spotLightData);

		///Call render() on all gameobjects
		void renderAllGameObjs() const;
		void updateAll(float elapsedTime);

		///Get the number of gameobjects
		int getNumGameObjects();
		///Access the player gameobject
		GameObject* getPlayerObject() { return mGameObjMap[PLAYER_OBJ_ID]; }

	private:
		static GameObjectId msNextUnitId;

		ComponentManager* mpComponentManagerHandle;

		MemoryPool mGameObjectPool;
		std::map<GameObjectId, GameObject*> mGameObjMap;
};

#endif // !GAME_OBJ_MAN_H
