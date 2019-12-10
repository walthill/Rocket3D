/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 GameApp.cpp
	=========================
********/

#include "GameApp.h"
#include <core/EngineCore.h>
#include <iostream>
#include <DeanLib/PerformanceTracker.h>
#include "../../RocketEngine/shader/ShaderManager.h"
#include "../input/GameMessage.h"
#include "../input/GameMessageManager.h"
#include "../../RocketEngine/logging/RK_Log.h"
#include "GameObjectManager.h"
#include "../component/ComponentManager.h"

GameApp* GameApp::mpGameApp = nullptr;

GameApp::~GameApp()
{
	clean();
}


bool GameApp::initialize(char* argv[])
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
	pPerformanceTracker->startTracking(mINIT_TRACKER_NAME);

	mpRocketEngine = new EngineCore();
	mpGameMessageManager = new GameMessageManager();
	mpMasterTimer = new Timer();

	if (!mpRocketEngine->initialize(argv))
		return false;

	mpGameObjectManager = new GameObjectManager(MAX_NUM_OBJECTS);
	mpComponentManager = new ComponentManager(MAX_NUM_OBJECTS, mpRocketEngine->getShaderManager(), STANDARD_SHADER_KEY);
	
	//=========================================================================
	//		Creating GameObjects
	//=========================================================================

	TransformData t = { Vector3(0, -1, -3), Vector3::one * 0.5f, Vector3::up, 45.0f };
	
	MeshComponentData meshData = {"cube", STANDARD_SHADER_KEY, mpRocketEngine->getShaderManager()->getShaderByKey(STANDARD_SHADER_KEY)};
	
	//MaterialData matData = { meshData.shader, STANDARD_SHADER };
	
	GameObject* o =	mpGameObjectManager->createGameObject(t, meshData);// , matData);


	TransformData t2 = { Vector3(1.5f,  -1.5f, -2.5f), Vector3::one * 0.1f, Vector3::up, 0 };

	MeshComponentData lightMeshData = { "cube", EMITTER_SHADER_KEY, mpRocketEngine->getShaderManager()->getShaderByKey(EMITTER_SHADER_KEY) };
	
	float constant = 1.0f, linear = 0.09f, quadratic = 0.032f;
	Vector3	ambient = Vector3(0.075f, 0.075f, 0.075f),
			diffuse = Vector3(0.8f, 0.8f, 0.8f),
			specular = Vector3(0.5f, 0.5f, 0.5f);
	Vector3* pointLightPositions;
	
	pointLightPositions = new Vector3[4]{
		Vector3(0.7f,  0.2f,  2.0f),
		Vector3(2.3f, -3.3f, -4.0f),
		Vector3(-4.0f,  2.0f, -12.0f),
		Vector3(0.0f,  -1.0f, -1.0f)
	};

	BaseLightData baseLightData = { ambient, diffuse, specular };

	PointLightData pointLightData;
	pointLightData.mBaseLightData = baseLightData;
	pointLightData.mConstant = constant;
	pointLightData.mLinear = linear;
	pointLightData.mQuadratic = quadratic;

	MeshComponentData dirLightMeshData = { "null", EMITTER_SHADER_KEY, mpRocketEngine->getShaderManager()->getShaderByKey(EMITTER_SHADER_KEY) };

	DirectionalLightData dirData;
	dirData.mBaseLightData = baseLightData;
	dirData.mDirection = Vector3(-0.2f, -1.0f, -0.3f);

	SpotLightData spotData;
	spotData.mBaseLightData = { Vector3::zero, Vector3::one, Vector3::one };
	spotData.mConstant = constant;
	spotData.mLinear = linear;
	spotData.mQuadratic = quadratic;
	spotData.mCutoff = cos(RK_Math::degToRad(12.5f));
	spotData.mOuterCutoff = cos(RK_Math::degToRad(17.5f));
	spotData.mpCamHandle = mpRocketEngine->getCamera();

	//Point lights
	for (size_t i = 0; i < 4; i++)
	{
		t2.position = pointLightPositions[i];
		GameObject* pointLight = mpGameObjectManager->createGameObject(t2, lightMeshData);
		pointLightData.mPosition = pointLightPositions[i];
		mpGameObjectManager->addPointLight(pointLight->getId(), pointLightData);
	}

	//Directional light
	GameObject* dirLight = mpGameObjectManager->createGameObject(t2, lightMeshData);
	mpGameObjectManager->addDirectionalLight(dirLight->getId(), dirData);

	//Spotlight light
	GameObject* spotLight = mpGameObjectManager->createGameObject();
	mpGameObjectManager->addSpotLight(spotLight->getId(), spotData);


	//=========================================================================

	pPerformanceTracker->stopTracking(mINIT_TRACKER_NAME);
	RK_INFO_ALL("Time to init: " + std::to_string(pPerformanceTracker->getElapsedTime(mINIT_TRACKER_NAME)) + "ms\n");
	
	delete[] pointLightPositions;
	delete pPerformanceTracker;

	mShouldExit = false;

	mpMasterTimer->start();

	return true;
}

void GameApp::clean()
{
	delete mpGameObjectManager;
	delete mpComponentManager;

	delete mpFrameTimer;
	delete mpMasterTimer;
	delete mpGameMessageManager;
	delete mpRocketEngine;
}

bool GameApp::processLoop()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker();

	mpFrameTimer = new Timer();
	
	while (!mShouldExit)
	{
		pPerformanceTracker->clearTracker(mLOOP_TRACKER_NAME);
		pPerformanceTracker->startTracking(mLOOP_TRACKER_NAME);

		mpFrameTimer->start();

		pPerformanceTracker->clearTracker(mDRAW_TRACKER_NAME);
		pPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);
	
		update();
		render();

		pPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);
		mpFrameTimer->sleepUntilElapsed(m60FPS_FRAME_TIME);
		pPerformanceTracker->stopTracking(mLOOP_TRACKER_NAME);

		RK_INFO_C("loop took:" + std::to_string(pPerformanceTracker->getElapsedTime(mLOOP_TRACKER_NAME)) + 
				  "ms draw took:" +  std::to_string(pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME)) +"ms\n");
		//mFPS = (int)(1000.0 / pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME));
		//RK_INFO_C("FPS: " + std::to_string(mFPS));
	}

	delete pPerformanceTracker;
	
	return false;
}
  
void GameApp::update()
{
	mpGameMessageManager->processMessagesForThisFrame();
	mpRocketEngine->update(); 
	mpComponentManager->update(mpRocketEngine->deltaTime);
	mpGameObjectManager->updateAll(mpRocketEngine->deltaTime);
}

void GameApp::render()
{
	mpRocketEngine->render();
	mpComponentManager->renderMeshes();
	mpRocketEngine->swapBuffers();
}

double GameApp::getCurrentTime() 
{ 
	return mpMasterTimer->getElapsedTime(); 
};

//TODO: everything below this point should be moved into separate classes and accessed via accessor
// -----------------------------------


void GameApp::moveForward() //TODO: add movement functions to a player class
{
	mpRocketEngine->moveCameraForward();
}

void GameApp::moveBack()
{
	mpRocketEngine->moveCameraBack();
}

void GameApp::moveRight()
{
	mpRocketEngine->moveCameraRight();
}

void GameApp::moveLeft()
{
	mpRocketEngine->moveCameraLeft();
}

void GameApp::toggleView(bool displayWireframeMode)
{
	mpRocketEngine->toggleWireframe(displayWireframeMode);
}