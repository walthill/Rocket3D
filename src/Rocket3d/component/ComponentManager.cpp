#include "ComponentManager.h"
#include "../../RocketEngine/asset/Model.h"

ComponentId ComponentManager::msNextMaterialComponentId = 0;
ComponentId ComponentManager::msNextMeshComponentId = 0;
ComponentId ComponentManager::msNextTransformComponentId = 0;

ComponentManager::ComponentManager(uint32 maxSize)
	:mTransformPool(maxSize, sizeof(TransformComponent))
	, mMaterialPool(maxSize, sizeof(MaterialComponent))
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

	//clear maps
	mTransformComponentMap.clear();
	mMaterialComponentMap.clear();
	mMeshComponentMap.clear();

	//reset memory pools
	mTransformPool.reset();
	mMaterialPool.reset();
	mMeshPool.reset();
}

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
//		pComponent->load();			//load model mesh
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

MaterialComponent* ComponentManager::getMaterialComponent(const ComponentId& id)
{
	auto it = mMaterialComponentMap.find(id);

	if (it != mMaterialComponentMap.end())
		return it->second;
	else
		return nullptr;
}

ComponentId ComponentManager::allocateMaterialComponent(const ComponentId& materialId, const MaterialData& data)
{
	ComponentId newID = INVALID_COMPONENT_ID;

	Byte* ptr = mMaterialPool.allocateObject();
	if (ptr != nullptr)
	{
		newID = msNextMaterialComponentId;
		MaterialComponent* pComponent = new (ptr)MaterialComponent(newID);
		pComponent->setData(data);
		mMaterialComponentMap[newID] = pComponent;
		msNextMaterialComponentId++;//increment id
	}

	return newID;
}

void ComponentManager::deallocateMaterialComponent(const ComponentId& id)
{
	auto it = mMaterialComponentMap.find(id);

	if (it != mMaterialComponentMap.end())//found it
	{
		MaterialComponent* ptr = it->second;
		mMaterialComponentMap.erase(it);

		ptr->~MaterialComponent();
		mMaterialPool.freeObject((Byte*)ptr);
	}
}


static std::mutex sMeshMutex;

static void loadMesh(std::vector<Model*>& models, std::string path)
{
	Model* newMesh = new Model(path);
	std::lock_guard<std::mutex> lock(sMeshMutex);
	models.push_back(newMesh);
}

void ComponentManager::loadMeshes()
{
#define ASYNC 1
#if ASYNC
	shouldLoadMesh = true;
	//load in from file
	for (auto it = mMeshComponentMap.begin(); it != mMeshComponentMap.end(); ++it)//found it
	{
		MeshComponentData* data = it->second->getData();
		if (!data->isLoaded)
		{
			std::string filename = modelFileLocation + data->modelName +
				"/" + data->modelName + ".obj";


			mFutures.push_back(std::async(
				std::launch::async, loadMesh, std::ref(mModelsToLoad), filename));
			mFuturesFinished.push_back(false);
		}
	}
#else
	for (auto it = mMeshComponentMap.begin(); it != mMeshComponentMap.end(); ++it)//found it
	{
		it->second->load();
	}
#endif	
}

void ComponentManager::storeMeshes()
{
	//do openGL buffer work
	for (size_t i = 0; i < mModelsToLoad.size(); i++)
	{
		mModelsToLoad[i]->initTextureBuffers();
	}

	int i = 0;
	for (auto it = mMeshComponentMap.begin(); it != mMeshComponentMap.end(); ++it)//found it
	{
		MeshComponentData* data = it->second->getData();
		if (!data->isLoaded)
		{
			data->mesh = mModelsToLoad[i];
			i++;
			data->isLoaded = true;
		}
	}
}

void ComponentManager::update(float elapsedTime)
{
	if (shouldLoadMesh)
	{
		int ready = 0;

		for (size_t i = 0; i < mFutures.size(); i++)
		{
			if (mFutures[i].wait_for(std::chrono::seconds(0)) == std::future_status::ready)
			{
				ready++;
				mFuturesFinished[i]  = true;
			}
		}

		if (ready == mFuturesFinished.size())
		{
			storeMeshes();
			shouldLoadMesh = false;
			mFutures.clear();
			mModelsToLoad.clear();
			mFutures.clear();
		}
	}
}

