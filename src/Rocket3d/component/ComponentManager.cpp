#include "ComponentManager.h"
#include "../../RocketEngine/asset/Model.h"

ComponentId ComponentManager::msNextMaterialComponentId = 0;
ComponentId ComponentManager::msNextMeshComponentId = 0;
ComponentId ComponentManager::msNextTransformComponentId = 0;
ComponentId ComponentManager::msNextPointLightComponentId = 0;
ComponentId ComponentManager::msNextDirectionalLightComponentId = 0;
ComponentId ComponentManager::msNextSpotlightComponentId = 0;

ComponentManager::ComponentManager(uint32 maxSize)
	: mTransformPool(maxSize, sizeof(TransformComponent))
	, mDirectionalLightPool(maxSize, sizeof(DirectionalLightComponent))
	, mPointLightPool(maxSize, sizeof(PointLightComponent))
	, mSpotlightPool(maxSize, sizeof(SpotLightComponent))
	, mMeshPool(maxSize, sizeof(MeshComponent))
{
}

ComponentManager::~ComponentManager()
{
	clean();
}

void ComponentManager::clean()
{
	//call destructor for all components
	for (auto& it : mTransformComponentMap)
	{
		TransformComponent* pComponent = it.second;
		pComponent->~TransformComponent();
	}
	for (auto& it : mMeshComponentMap)
	{
		MeshComponent* pComponent = it.second;
		pComponent->~MeshComponent();
	}
	for (auto& it : mMaterialComponentMap)
	{
		MaterialComponent* pComponent = it.second;
		pComponent->~MaterialComponent();
	}
	for (auto& it : mDirectionalLightComponentMap)
	{
		DirectionalLightComponent* pComponent = it.second;
		pComponent->~DirectionalLightComponent();
	}
	for (auto& it : mPointLightComponentMap)
	{
		PointLightComponent* pComponent = it.second;
		pComponent->~PointLightComponent();
	}
	for (auto& it : mSpotlightComponentMap)
	{
		SpotLightComponent* pComponent = it.second;
		pComponent->~SpotLightComponent();
	}

	//clear maps
	mTransformComponentMap.clear();
	mMaterialComponentMap.clear();
	mMeshComponentMap.clear();
	mDirectionalLightComponentMap.clear();
	mPointLightComponentMap.clear();
	mSpotlightComponentMap.clear();

	//reset memory pools
	mTransformPool.reset();
	mMeshPool.reset();
	mDirectionalLightPool.reset();
	mPointLightPool.reset();
	mSpotlightPool.reset();
}


/******************************************************************************
******************************************************************************

	TRANSFORM COMPONENT

******************************************************************************
*****************************************************************************/


TransformComponent * ComponentManager::getTransformComponent(const ComponentId & id)
{
	auto it = mTransformComponentMap.find(id);

	if (it != mTransformComponentMap.end())
		return it->second;
	else
		return nullptr;
}

ComponentId ComponentManager::allocateTransformComponent(const TransformData & data)
{
	ComponentId newID = INVALID_COMPONENT_ID;

	Byte* ptr = mTransformPool.allocateObject();
	if (ptr != nullptr)
	{
		newID = msNextTransformComponentId;
		TransformComponent* pComponent = new (ptr)TransformComponent(newID);
		pComponent->setData(data);
		mTransformComponentMap[newID] = pComponent;
		msNextTransformComponentId++;//increment id
	}

	return newID;
}

void ComponentManager::deallocateTransformComponent(const ComponentId & id)
{
	auto it = mTransformComponentMap.find(id);

	if (it != mTransformComponentMap.end())//found it
	{
		TransformComponent* ptr = it->second;
		mTransformComponentMap.erase(it);

		ptr->~TransformComponent();
		mTransformPool.freeObject((Byte*)ptr);
	}
}

/******************************************************************************
******************************************************************************

	MESH COMPONENT

******************************************************************************
*****************************************************************************/


MeshComponent * ComponentManager::getMeshComponent(const ComponentId & id)
{
	auto it = mMeshComponentMap.find(id);

	if (it != mMeshComponentMap.end())
		return it->second;
	else
		return nullptr;
}

//Load model and assign to gameobject
ComponentId ComponentManager::allocateMeshComponent(const ComponentId & meshId, const MeshComponentData & data)
{
	ComponentId newID = INVALID_COMPONENT_ID;
	Byte* ptr = mMeshPool.allocateObject();

	if (ptr != nullptr)
	{
		newID = msNextMeshComponentId;
		MeshComponent* pComponent = new (ptr)MeshComponent(newID);
		pComponent->setData(data);
		pComponent->load();			//load model mesh
		mMeshComponentMap[newID] = pComponent;
		msNextMeshComponentId++;//increment id
	}
	
	return newID;
}

void ComponentManager::deallocateMeshComponent(const ComponentId & id)
{
	auto it = mMeshComponentMap.find(id);

	if (it != mMeshComponentMap.end())//found it
	{
		MeshComponent* ptr = it->second;
		mMeshComponentMap.erase(it);

		ptr->~MeshComponent();
		mMeshPool.freeObject((Byte*)ptr);
	}
}



/******************************************************************************
******************************************************************************

	DIRECTIONAL LIGHT COMPONENT

******************************************************************************
*****************************************************************************/


DirectionalLightComponent* ComponentManager::getDirectionalLightComponent(const ComponentId& id)
{
	auto it = mDirectionalLightComponentMap.find(id);

	if (it != mDirectionalLightComponentMap.end())
		return it->second;
	else
		return nullptr;
}

ComponentId ComponentManager::allocateDirectionalLightComponent(const ComponentId& meshId, const DirectionalLightData& data)
{
	ComponentId newID = INVALID_COMPONENT_ID;
	Byte* ptr = mDirectionalLightPool.allocateObject();

	if (ptr != nullptr)
	{
		newID = msNextDirectionalLightComponentId;
		DirectionalLightComponent* pComponent = new (ptr)DirectionalLightComponent(newID);
		pComponent->setData(data);
		mDirectionalLightComponentMap[newID] = pComponent;
		msNextDirectionalLightComponentId++;//increment id
	}

	return newID;
}

void ComponentManager::deallocateDirectionalLightComponent(const ComponentId& id)
{
	auto it = mDirectionalLightComponentMap.find(id);

	if (it != mDirectionalLightComponentMap.end())//found it
	{
		DirectionalLightComponent* ptr = it->second;
		mDirectionalLightComponentMap.erase(it);

		ptr->~DirectionalLightComponent();
		mDirectionalLightPool.freeObject((Byte*)ptr);
	}
}

/******************************************************************************
******************************************************************************

	POINT LIGHT COMPONENT

******************************************************************************
*****************************************************************************/


PointLightComponent* ComponentManager::getPointLightComponent(const ComponentId& id)
{
	auto it = mPointLightComponentMap.find(id);

	if (it != mPointLightComponentMap.end())
		return it->second;
	else
		return nullptr;
}

ComponentId ComponentManager::allocatePointLightComponent(const ComponentId& meshId, const PointLightData& data)
{
	ComponentId newID = INVALID_COMPONENT_ID;
	Byte* ptr = mPointLightPool.allocateObject();

	if (ptr != nullptr)
	{
		newID = msNextPointLightComponentId;
		PointLightComponent* pComponent = new (ptr)PointLightComponent(newID);
		pComponent->setData(data);
		mPointLightComponentMap[newID] = pComponent;
		msNextPointLightComponentId++;//increment id
	}

	return newID;
}

void ComponentManager::deallocatePointLightComponent(const ComponentId& id)
{
	auto it = mPointLightComponentMap.find(id);

	if (it != mPointLightComponentMap.end())//found it
	{
		PointLightComponent* ptr = it->second;
		mPointLightComponentMap.erase(it);

		ptr->~PointLightComponent();
		mPointLightPool.freeObject((Byte*)ptr);
	}
}


/******************************************************************************
******************************************************************************

	SPOT LIGHT COMPONENT

******************************************************************************
*****************************************************************************/

SpotLightComponent* ComponentManager::getSpotlightComponent(const ComponentId& id)
{
	auto it = mSpotlightComponentMap.find(id);

	if (it != mSpotlightComponentMap.end())
		return it->second;
	else
		return nullptr;
}

ComponentId ComponentManager::allocateSpotlightComponent(const ComponentId& meshId, const SpotLightData& data)
{
	ComponentId newID = INVALID_COMPONENT_ID;
	Byte* ptr = mSpotlightPool.allocateObject();

	if (ptr != nullptr)
	{
		newID = msNextSpotlightComponentId;
		SpotLightComponent* pComponent = new (ptr)SpotLightComponent(newID);
		pComponent->setData(data);
		mSpotlightComponentMap[newID] = pComponent;
		msNextSpotlightComponentId++;//increment id
	}

	return newID;
}

void ComponentManager::deallocateSpotlightComponent(const ComponentId& id)
{
	auto it = mSpotlightComponentMap.find(id);

	if (it != mSpotlightComponentMap.end())//found it
	{
		SpotLightComponent* ptr = it->second;
		mSpotlightComponentMap.erase(it);

		ptr->~SpotLightComponent();
		mSpotlightPool.freeObject((Byte*)ptr);
	}
}


void ComponentManager::update(float elapsedTime)
{
	processLightingComponents();
}

void ComponentManager::processLightingComponents()
{
	for (auto& it : mDirectionalLightComponentMap)
		it.second->processLightingData(lightingShader);

	for (auto& it : mPointLightComponentMap)
		it.second->processLightingData(lightingShader);

	for (auto& it : mSpotlightComponentMap)
		it.second->processLightingData(lightingShader);

}

