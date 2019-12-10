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

class GameObjectManager : public Trackable
{
	public:
		GameObjectManager(uint32 maxSize);
		~GameObjectManager();
		
		GameObject* findGameObject(const GameObjectId& id) const;
		
		GameObject* createGameObject(const TransformData& transform = ZERO_TRANSFORM_DATA, 
									const MeshComponentData& meshData = ZERO_MESH_DATA, 
									/*const MaterialData& matData = ZERO_MAT_DATA, */
									const GameObjectId& id = INVALID_GAMEOBJECT_ID);

		void destroy(const GameObjectId& id);

		void addPointLight(const GameObjectId& id, const PointLightData& pointLightData);
		void addDirectionalLight(const GameObjectId& id, const DirectionalLightData& dirLightDat);
		void addSpotLight(const GameObjectId& id, const SpotLightData& spotlightData);

		void renderAllGameObjs() const;
		void updateAll(float elapsedTime);

		int getNumGameObjects();
		GameObject* getPlayerObject() { return mGameObjMap[PLAYER_OBJ_ID]; }

	private:
		static GameObjectId msNextUnitId;

		ComponentManager* mpComponentManagerHandle;

		MemoryPool mGameObjectPool;
		std::map<GameObjectId, GameObject*> mGameObjMap;
};

#endif // !GAME_OBJ_MAN_H
