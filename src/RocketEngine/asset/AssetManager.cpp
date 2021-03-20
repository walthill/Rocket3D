#include "AssetManager.h"
#include "Model.h"

AssetManager* AssetManager::mpAssetManagerInstance = nullptr;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	clean();
}

bool AssetManager::initialize()
{
	bool success = false;

	mModelAssetCache = std::map<std::string, Model*>();

	return success;
}

void AssetManager::clean()
{
	auto iter = mModelAssetCache.begin();

	for (iter; iter != mModelAssetCache.end(); ++iter)
	{
		delete iter->second;
	}
}

Model* AssetManager::loadModelAsset(std::string path)
{
	auto key = path.substr(path.find_last_of('/')+1, path.find_last_of('.'));
	auto iter = mModelAssetCache.find(key);

	if (iter != mModelAssetCache.end())
	{
		return iter->second;
	}
	else
	{
		Model* newModel = new Model(path);
		mModelAssetCache[key] = newModel;

		return newModel;
	}
}


