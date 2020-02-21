/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 EngineCore.cpp
	=========================

********/
//#include <glfw3.h>
#include "../../Rocket3d/core/Application.h"
#include "EngineCore.h"
//#include "../window/Window.h"
#include "../render/Camera.h"
#include "../asset/image/RocketImgLoader.h"
//#include "../input/InputSystem.h"
//#include "../shader/ShaderBuild.h"
#include "../shader/RK_Shader.h"
#include "../shader/ShaderManager.h"
#include "../logging/RK_Log.h"
#include "../render/Text.h"


//mouse selection: http://antongerdelan.net/opengl/raycasting.html
// also helpful? https://www.bfilipek.com/2012/06/select-mouse-opengl.html

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
	clean();
}

void EngineCore::clean()
{
	delete textObj;
	delete textObj2;
	delete mpShaderManager;
//	delete mpInputSystem;
	delete mpCam;
}


void EngineCore::initLighting()
{
	mpShaderManager->useShaderByKey(standardLightingShaderId);
	mpShaderManager->setShaderInt("material.diffuse", 0);
	mpShaderManager->setShaderInt("material.specular", 1);
	mpShaderManager->setShaderFloat("material.shininess", 32.0f);
} 


bool EngineCore::initialize()
{
	Application* app = Application::getInstance();
	mWindowWidth = app->getAppWindow()->getWidth();
	mWindowHeight = app->getAppWindow()->getHeight();
	mpWindowHandle = app->getAppWindow();

	mpCam = new Camera(rkm::Vector3(0.0f, 0.0f, 3.0f));

//	mpInputSystem = new InputSystem(mpWindowHandle->getWindowHandle());
	mpShaderManager = new ShaderManager();

	mpShaderManager->addShader(standardLightingShaderId, new RK_Shader("vLighting.glsl", "fLighting.glsl"));
	mpShaderManager->addShader(emitterShaderId, new RK_Shader("vLamp.glsl", "fLamp.glsl"));
	mpShaderManager->addShader(textShaderId, new RK_Shader("vTextRender.glsl", "fTextRender.glsl"));

	initLighting();

	processViewProjectionMatrices();

	textObj = new Text("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId));
	TextData data = { "This is sample text", Color(127, 204, 51), rkm::Vector2(25.0f, 25.0f), 1.0f };
	textObj->initTextData(data);
	textObj2 = new Text("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId));
	data = { "(C) Rocket3d", Color(76.5f, 178.5f, 229.5f), rkm::Vector2(540.0f, 570.0f), 0.5f };
	textObj2->initTextData(data);
	// Compile and setup the shader
	rkm::Mat4 projection = rkm::MatProj::orthographic(0.0f, 800.0f, 0.0f, 600.0f);
	mpShaderManager->useShaderByKey(textShaderId);
	mpShaderManager->getShaderInUse()->setMat4("projection", projection);
	return true;
}


void EngineCore::update()
{
	//mpInputSystem->processInput();
	calculateDeltaTime();
}

void EngineCore::calculateDeltaTime()
{
	float currentFrame = (float)Application::getInstance()->getTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

//Set vertex shader uniform data for each shader
void EngineCore::processViewProjectionMatrices()
{
	Application* app = Application::getInstance();

	mpShaderManager->useShaderByKey(standardLightingShaderId);
	rkm::Mat4 proj = rkm::Mat4::identity;
	proj = rkm::MatProj::perspective(rkm::degToRad(mpCam->getFov()), (float)app->getAppWindow()->getWidth() / (float)app->getAppWindow()->getHeight(), 0.1f, 100.0f);
	mpShaderManager->setShaderMat4("projection", proj);

	rkm::Mat4 view = rkm::Mat4::identity;
	view = mpCam->getViewMatrix();
	mpShaderManager->setShaderMat4("view", view);

	rkm::Mat4 model = rkm::Mat4::identity;

	// Light "emitters" are not affected by the lighting shader 
	// and mark the location of the light sources
	mpShaderManager->useShaderByKey(emitterShaderId);
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);
}

void EngineCore::render()
{
	processViewProjectionMatrices();
	textObj->renderText();
	textObj2->renderText();
}

void EngineCore::moveCameraLeft()
{
	mpCam->moveCameraLeft(deltaTime);
}

void EngineCore::moveCameraRight()
{
	mpCam->moveCameraRight(deltaTime);
}

void EngineCore::moveCameraForward()
{
	mpCam->moveCameraForward(deltaTime);
}

void EngineCore::moveCameraBack()
{
	mpCam->moveCameraBack(deltaTime);
}

void EngineCore::toggleWireframe(bool showWireframe)
{
	mpWindowHandle->toggleWireframe(showWireframe);
}
