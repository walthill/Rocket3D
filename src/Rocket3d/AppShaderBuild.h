#pragma once

#include "../RocketBuild/R3_ShaderBuild.h"

#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

#include <Windows.h>

#include "ShaderManager.h"

// Resource https://nlguillemot.wordpress.com/2018/02/16/simple-live-c-reloading-in-visual-studio/

struct ReloadableCpp
{
	std::wstring DLLPath;
	std::vector<std::string> ProcsToLoad;

	HMODULE Module = NULL;
	uint64_t LastWrite = 0;
	std::map<std::string, void*> Procs;
};

class AppShaderBuild
{
public:
	void init(std::wstring path)
	{
		ReloadableCpp *rcpp = new ReloadableCpp();
		// Specify the path to the DLL and the functions we want to load from it.
		rcpp->DLLPath = path.c_str();
		rcpp->ProcsToLoad = { };

//		mReloadableSourceList = {};
		mReloadableSourceList.push_back(rcpp);
	}

	void addFunctionToLiveLoad(std::string functionName, int reloadCppIndex = 0)
	{
		mReloadableSourceList[reloadCppIndex]->ProcsToLoad.push_back(functionName);
	}

	void pollSourceForUpdates(ShaderManager* shaderMan)
	{
		checkForCodeChanges();
		buildShaders(shaderMan);
	}

private:

	// Checks if the DLL has been changed, and if so, reloads the functions from it.
	void checkForCodeChanges()
	{
		for (const auto& reloadCpp : mReloadableSourceList)
		{
			// Try opening the DLL's file
			HANDLE hDLLFile = CreateFileW(reloadCpp->DLLPath.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hDLLFile == INVALID_HANDLE_VALUE)
			{
				return;
			}

			// Check if the DLL has changed since we last loaded it.
			uint64_t lastWriteTime;
			if (GetFileTime(hDLLFile, NULL, NULL, (FILETIME*)&lastWriteTime) &&
				reloadCpp->LastWrite < lastWriteTime)
			{
				mShouldReload = true;

				// Remove all references to the old module
				if (reloadCpp->Module)
				{
					FreeLibrary((HMODULE)reloadCpp->Module);
					reloadCpp->Module = NULL;
					reloadCpp->Procs.clear();
				}

				// Copy the DLL so we don't hold a lock on the original file.
				std::wstring tmpname = reloadCpp->DLLPath + L".rcpp.dll";
				if (CopyFileW(reloadCpp->DLLPath.c_str(), tmpname.c_str(), FALSE))
				{
					// Load the copied DLL and get the functions from it.
					reloadCpp->Module = LoadLibraryW(tmpname.c_str());
					if (reloadCpp->Module)
					{
						for (const auto& p : reloadCpp->ProcsToLoad)
						{
							reloadCpp->Procs[p] = GetProcAddress((HMODULE)reloadCpp->Module, p.c_str());
						}
						reloadCpp->LastWrite = lastWriteTime;
					}
				}
			}

			// Boy Scout Rule!
			CloseHandle(hDLLFile);
		}
	}

	void buildShaders(ShaderManager* shaderMan)
	{
		for (const auto& reloadCpp : mReloadableSourceList)
		{
			for (auto functionName : reloadCpp->ProcsToLoad)
			{
				auto live_shader_rebuild_ptr = (decltype(live_shader_rebuild)*)reloadCpp->Procs[functionName];

				// If loading the function pointer worked properly, we can call it. Only call if changed?
				if (live_shader_rebuild_ptr && mShouldReload)
				{
					live_shader_rebuild_ptr(&ShaderManager::buildShaders);
					mShouldReload = false;
				}
//				else { firstRun = false;  std::cout << "FALSE"; }

			}
		}
	}

	std::vector<ReloadableCpp*> mReloadableSourceList;
	bool mShouldReload = false, firstRun = true;
};