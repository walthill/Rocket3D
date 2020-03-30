#include "GameObjectManager.h"
#include "../../Rocket3d/core/GameApp.h"
#include "EngineCore.h"

GameObjectId GameObjectManager::msNextUnitId = PLAYER_OBJ_ID + 1;

GameObjectManager::GameObjectManager(uint32 maxSize) :
	mGameObjectPool(maxSize, sizeof(GameObject))
{
}

GameObjectManager::~GameObjectManager()
{
	mpComponentManagerHandle = nullptr;
}

GameObject* GameObjectManager::createGameObject(const TransformData& transform, const MeshComponentData& meshData,
												 /* not implemented const MaterialData& matData,*/
												const GameObjectId& id)
{
	GameObject* newObj = nullptr;

	rkutil::Byte* ptr = mGameObjectPool.allocateObject();
	
	if (ptr != nullptr)
	{
		newObj = ::new (ptr)GameObject();//placement new

		GameObjectId newId = id;
		if (newId == INVALID_GAMEOBJECT_ID) //new game obj
		{
			newId = msNextUnitId;
			msNextUnitId++;
		}
				
		//add new object to map and set the object's id locally
		mGameObjMap[newId] = newObj;
		newObj->setId(newId);

		//Hook up components
		ComponentManager* pComponentManager = GameApp::getInstance()->getRocketEngine()->getComponentManager();
		
		//TRANSFORM
		ComponentId newTransformId = pComponentManager->allocateTransformComponent(transform);
		newObj->connectTransform(newTransformId);
		newObj->setTransformHandle(pComponentManager->getTransformComponent(newTransformId));
	
		//MESH
		//Create mesh component, store id in new object, and load the mesh to the component
		ComponentId newMeshId = pComponentManager->allocateMeshComponent(newObj->getTransformId(), meshData);
		newObj->connectMesh(newMeshId);

	}
	return newObj;
}


GameObject* GameObjectManager::findGameObject(const GameObjectId & id) const
{
	auto it = mGameObjMap.find(id);

	if (it != mGameObjMap.end())//found?
		return it->second;
	else
		return nullptr;
}

void GameObjectManager::destroy(const GameObjectId & id)
{
	auto it = mGameObjMap.find(id);
	if (it != mGameObjMap.end())//found?
	{
		GameObject* obj = it->second;//hold for later

		//remove from map
		mGameObjMap.erase(it);

		//remove components from manager
		ComponentManager* pComponentManager = GameApp::getInstance()->getRocketEngine()->getComponentManager();
		pComponentManager->deallocateTransformComponent(obj->getTransformId());

		//call destructor on gameObj
		obj->~GameObject();

		//free the object in the pool
		mGameObjectPool.freeObject((rkutil::Byte*)obj);
	}
}

void GameObjectManager::addPointLight(const GameObjectId& id, const PointLightData& pointLightData)
{
	ComponentManager* pComponentManager = GameApp::getInstance()->getRocketEngine()->getComponentManager();
	GameObject* obj = mGameObjMap[id];

	ComponentId pointLight = pComponentManager->allocatePointLightComponent(obj->getTransformId(), pointLightData);
	obj->connectPointLight(pointLight);
}

void GameObjectManager::addDirectionalLight(const GameObjectId& id, const DirectionalLightData& dirLightDat)
{
	ComponentManager* pComponentManager = GameApp::getInstance()->getRocketEngine()->getComponentManager();
	GameObject* obj = mGameObjMap[id];

	ComponentId dirLight = pComponentManager->allocateDirectionalLightComponent(obj->getTransformId(), dirLightDat);
	obj->connectDirectionalLight(dirLight);
}

void GameObjectManager::addSpotLight(const GameObjectId& id, const SpotLightData& spotlightData)
{
	ComponentManager* pComponentManager = GameApp::getInstance()->getRocketEngine()->getComponentManager();
	GameObject* obj = mGameObjMap[id];

	ComponentId spotLight = pComponentManager->allocateSpotlightComponent(obj->getTransformId(), spotlightData);
	obj->connectSpotLight(spotLight);
}

void GameObjectManager::renderAllGameObjs() const
{
	/*for (auto it = mGameObjMap.begin(); it != mGameObjMap.end(); ++it)
	{
		it->second->render();
	}*/
}

void GameObjectManager::updateAll(float elapsedTime)
{
	for (auto it = mGameObjMap.begin(); it != mGameObjMap.end(); ++it)
	{
		//no update function currently
		it->second->update(elapsedTime);
	}
}

int GameObjectManager::getNumGameObjects()
{
	return mGameObjMap.size();
}
