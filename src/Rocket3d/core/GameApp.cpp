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
#include "Application.h"
#include <core/EngineCore.h>
#include <rkutil/Timer.h>
#include <rkutil/MemoryTracker.h>
#include <rkutil/PerformanceTracker.h>
#include "../../RocketEngine/shader/ShaderManager.h"
//#include "../input/Message.h"
//#include "../input/MessageManager.h"
#include <component/TransformComponent.h>
#include <component/MeshComponent.h>
#include <component/LightComponent.h>
#include "../../RocketEngine/core/GameObject.h"
#include <core/GameObjectManager.h>

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
	mpMasterTimer = new rkutil::Timer();

	if (!mpRocketEngine->initialize())
		return false;
	
	//=========================================================================
	//		Creating GameObjects
	//=========================================================================
	
	//MeshComponentData meshData = { "cube", STANDARD_SHADER_KEY, mpRocketEngine->getShaderManager()->getShaderByKey(STANDARD_SHADER_KEY) };
	//MeshComponentData meshData = {"cube.obj", STANDARD_SHADER_KEY, mpRocketEngine->getShaderManager()->getShaderByKey(STANDARD_SHADER_KEY)};
	//MeshComponentData meshData = { "cube", "refractionShader", mpRocketEngine->getShaderManager()->getShaderByKey("refractionShader") };
	//GameObject* o =	mpRocketEngine->getGameObjectManager()->createGameObject(t, meshData);// , matData);


	//Lighting GameObjects
	TransformData t2 = { rkm::Vector3(1.5f,  -1.5f, -2.5f), rkm::Vector3::one * 0.1f, rkm::Vector3::up, 0 };

	MeshComponentData lightMeshData = { "cube.obj", EMITTER_SHADER_KEY, mpRocketEngine->getShaderManager()->getShaderByKey(EMITTER_SHADER_KEY) };
	
	float constant = 1.0f, linear = 0.09f, quadratic = 0.032f;

	//TODO: have these values stored as Color objects
	rkm::Vector3	ambient = rkm::Vector3(0.000f, 0.000f, 0.000f),
			diffuse = rkm::Vector3(1.8f, 1.8f, 1.8f),
			specular = rkm::Vector3(0.5f, 0.5f, 0.5f);
	rkm::Vector3* pointLightPositions;
	
	pointLightPositions = new rkm::Vector3[4]{
		rkm::Vector3(0.0f,  0.0f,  2.0f),
		rkm::Vector3(2.3f,	1.5f, -4.0f),
		rkm::Vector3(0.7f,  1.5f,  2.0f)
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
	spotData.mpCamHandle = mpRocketEngine->getGameCamera();

	//TODO: fix z-axis for gameobjects to match shader Z axis??
	//Point lights
	for (size_t i = 0; i < 1; i++)
	{
		t2.position = rkm::Vector3(pointLightPositions[i].getX(), pointLightPositions[i].getY(), -pointLightPositions[i].getZ());
		GameObject* pointLight = mpRocketEngine->getGameObjectManager()->createGameObject(t2, lightMeshData);
		pointLightData.mPosition = pointLightPositions[i];
		mpRocketEngine->getGameObjectManager()->addPointLight(pointLight->getId(), pointLightData);
	}

	//Directional light
	//GameObject* dirLight = mpRocketEngine->getGameObjectManager()->createGameObject(t2, lightMeshData);
	//mpRocketEngine->getGameObjectManager()->addDirectionalLight(dirLight->getId(), dirData);

	//Spotlight light
	//GameObject* spotLight = mpRocketEngine->getGameObjectManager()->createGameObject();
	//mpRocketEngine->getGameObjectManager()->addSpotLight(spotLight->getId(), spotData);
	
	//=========================================================================

	pPerformanceTracker->stopTracking(mINIT_TRACKER_NAME);
	RK_INFO_ALL("Time to init: " + std::to_string(pPerformanceTracker->getElapsedTime(mINIT_TRACKER_NAME)) + "ms\n");
	
	delete[] pointLightPositions;
	delete pPerformanceTracker;

	mpAppHandle = Application::getInstance();
	mKeepRunning = true;

	mpPerformanceTracker = new rkutil::PerformanceTracker();
	mpFrameTimer = new rkutil::Timer();

	//render first scene frame when running engine editor app
	update();
	render();

	mpMasterTimer->start();

	return true;
}

void GameApp::clean()
{
	delete mpPerformanceTracker;
	delete mpFrameTimer;
	delete mpMasterTimer;
	delete mpRocketEngine;
}

bool GameApp::processLoop()
{
	if (mpAppHandle->isPlaying())
	{
		//GameApp loop is now unecessary. the app loop is handled by Application. 
		//This class is called in the GameLayer and looped through onUpdate()
		//while (!mShouldExit)

		mpPerformanceTracker->startTracking(mLOOP_TRACKER_NAME);

		mpFrameTimer->start();

		mpPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);

		update();
		render();

		mpPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);
		mpFrameTimer->sleepUntilElapsed(FRAME_TIME_60FPS);
		mpPerformanceTracker->stopTracking(mLOOP_TRACKER_NAME);

		RK_INFO_C("loop took:" + std::to_string(mpPerformanceTracker->getElapsedTime(mLOOP_TRACKER_NAME)) +
			"ms draw took:" + std::to_string(mpPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME)) + "ms\n");
		//mFPS = (int)(1000.0 / mpPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME));
		//RK_INFO_C("FPS: " + std::to_string(mFPS));
	}

	return mKeepRunning;
}
  
void GameApp::update()
{
	mpRocketEngine->update(); 
}

void GameApp::render()
{
	mpRocketEngine->render(EngineCore::GAME_VIEW);
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