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
#include "../../RocketEngine/shader/ShaderManager.h"
//#include "../input/Message.h"
//#include "../input/MessageManager.h"
#include "GameObjectManager.h"
#include "../component/ComponentManager.h"
#include <window/Window.h>

GameApp* GameApp::mpGameApp = nullptr;

GameApp::~GameApp()
{
	clean();
}

bool GameApp::initialize()
{
	rkutil::PerformanceTracker* pPerformanceTracker = new rkutil::PerformanceTracker();
	pPerformanceTracker->startTracking(mINIT_TRACKER_NAME);

	mpRocketEngine = new EngineCore();
//	mpGameMessageManager = new GameMessageManager();
	mpMasterTimer = new rkutil::Timer();

	if (!mpRocketEngine->initialize())
		return false;

	mpGameObjectManager = new GameObjectManager(MAX_NUM_OBJECTS);
	mpComponentManager = new ComponentManager(MAX_NUM_OBJECTS, mpRocketEngine->getShaderManager(), STANDARD_SHADER_KEY);
	
	//=========================================================================
	//		Creating GameObjects
	//=========================================================================

	TransformData t = { rkm::Vector3(0, -1, -3), rkm::Vector3::one * 0.5f, rkm::Vector3::up, 45.0f };
	
	MeshComponentData meshData = {"cube", STANDARD_SHADER_KEY, mpRocketEngine->getShaderManager()->getShaderByKey(STANDARD_SHADER_KEY)};
	
	//MaterialData matData = { meshData.shader, STANDARD_SHADER };
	
	GameObject* o =	mpGameObjectManager->createGameObject(t, meshData);// , matData);


	TransformData t2 = { rkm::Vector3(1.5f,  -1.5f, -2.5f), rkm::Vector3::one * 0.1f, rkm::Vector3::up, 0 };

	MeshComponentData lightMeshData = { "cube", EMITTER_SHADER_KEY, mpRocketEngine->getShaderManager()->getShaderByKey(EMITTER_SHADER_KEY) };
	
	float constant = 1.0f, linear = 0.09f, quadratic = 0.032f;

	//TODO: have these values stored as Color objects
	rkm::Vector3	ambient = rkm::Vector3(0.075f, 0.075f, 0.075f),
			diffuse = rkm::Vector3(0.8f, 0.8f, 0.8f),
			specular = rkm::Vector3(0.5f, 0.5f, 0.5f);
	rkm::Vector3* pointLightPositions;
	
	pointLightPositions = new rkm::Vector3[4]{
		rkm::Vector3(0.7f,  0.2f,  2.0f),
		rkm::Vector3(2.3f, -3.3f, -4.0f),
		rkm::Vector3(-4.0f,  2.0f, -12.0f),
		rkm::Vector3(0.0f,  -1.0f, -1.0f)
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
	dirData.mDirection = rkm::Vector3(-0.2f, -1.0f, -0.3f);

	SpotLightData spotData;
	spotData.mBaseLightData = { rkm::Vector3::zero, rkm::Vector3::one, rkm::Vector3::one };
	spotData.mConstant = constant;
	spotData.mLinear = linear;
	spotData.mQuadratic = quadratic;
	spotData.mCutoff = cos(rkm::degToRad(12.5f));
	spotData.mOuterCutoff = cos(rkm::degToRad(17.5f));
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

	mpAppHandle = Application::getInstance();
	mKeepRunning = true;

	mpMasterTimer->start();

	return true;
}

void GameApp::clean()
{
	delete mpGameObjectManager;
	delete mpComponentManager;

	delete mpPerformanceTracker;
	delete mpFrameTimer;
	delete mpMasterTimer;
//	delete mpGameMessageManager;
	delete mpRocketEngine;
}

bool GameApp::processLoop()
{
	if (mpAppHandle->isPlaying())
	{

		mpPerformanceTracker = new rkutil::PerformanceTracker();

		mpFrameTimer = new rkutil::Timer();

		//GameApp loop is now unecessary. the app loop is handled by Application. 
		//This class is called in the GameLayer and looped through onUpdate()
		//while (!mShouldExit)
		{
			mpPerformanceTracker->startTracking(mLOOP_TRACKER_NAME);

			mpFrameTimer->start();

			mpPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);

			update();
			render();

			mpPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);
			mpFrameTimer->sleepUntilElapsed(m60FPS_FRAME_TIME);
			mpPerformanceTracker->stopTracking(mLOOP_TRACKER_NAME);

			RK_INFO_C("loop took:" + std::to_string(mpPerformanceTracker->getElapsedTime(mLOOP_TRACKER_NAME)) +
				"ms draw took:" + std::to_string(mpPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME)) + "ms\n");
			//mFPS = (int)(1000.0 / mpPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME));
			//RK_INFO_C("FPS: " + std::to_string(mFPS));
		}
	}

	return mKeepRunning;
}
  
void GameApp::update()
{
//	mpGameMessageManager->processMessagesForThisFrame(mpRocketEngine->deltaTime);
	mpRocketEngine->update(); 
	mpComponentManager->update(mpRocketEngine->deltaTime);
	mpGameObjectManager->updateAll(mpRocketEngine->deltaTime);
}

void GameApp::render()
{
	mpRocketEngine->render();
	mpComponentManager->renderMeshes();
	mpRocketEngine->renderText();
	mpRocketEngine->renderFramebufferScreen();
}

double GameApp::getCurrentTime() 
{ 
	return mpMasterTimer->getTimeElapsedMs(); 
}

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