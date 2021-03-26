#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include "../util/EngineUtils.h"
#include <map>
#include <rkm/Mat4.h>

class Model;

class AssetManager : public rkutil::Trackable
{
	public:
		#pragma region Static Class Functions
			/***
				* Initializes the global static instance of the AssetManager class
			***/
			static void initInstance()
			{
				if(mpAssetManagerInstance == nullptr)
					mpAssetManagerInstance = new AssetManager;
			}

			/***
				* Destroys the global static instance of the AssetManager class
			***/
			static void cleanInstance()
			{
				if (mpAssetManagerInstance != nullptr)
				{
					delete mpAssetManagerInstance;
					mpAssetManagerInstance = nullptr;
				}
			}

			/***
				* Accesses the global static instance of the AssetManager class.
			***/
			static AssetManager* getInstance()
			{
				RK_ASSERT(mpAssetManagerInstance != nullptr);
				return mpAssetManagerInstance;
			}
		#pragma endregion

		bool initialize();

		void clean();
		
		Model* loadModelAsset(std::string path, int instanceCount = 1, rkm::Mat4* matrices = nullptr); //take model name and make it the key, add to map if not there, else return model ref

	private:
		static AssetManager* mpAssetManagerInstance;
		std::map<std::string, Model*> mModelAssetCache;
		
		AssetManager();
		~AssetManager();
};

#endif // !ASSET_MANAGER_H
