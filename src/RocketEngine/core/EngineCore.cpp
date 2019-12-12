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
#include <glad/glad.h>
#include <glfw3.h>
#include "EngineCore.h"
#include "../window/Window.h"
#include "../render/Camera.h"
#include "../asset/image/RocketImgLoader.h"
#include "../input/InputSystem.h"
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
	delete mpInputSystem;
	delete mpCam;
	delete mpWindow;

	glfwTerminate();
}

void EngineCore::initGLFW()
{
	glfwInit();

	//Init OpenGL version settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

void EngineCore::initLighting()
{
	mpShaderManager->useShaderByKey(standardLightingShaderId);
	mpShaderManager->setShaderInt("material.diffuse", 0);
	mpShaderManager->setShaderInt("material.specular", 1);
	mpShaderManager->setShaderFloat("material.shininess", 32.0f);
} 

bool EngineCore::initialize(char* argv[])
{
	initGLFW();

	mpWindow = new Window();
	
	//Init window size, name, features, and cursor 
	if(!mpWindow->initialize(800, 600, "Rocket3D", DEPTH_TEST | AA_MULTISAMPLE, false))
		return false;

	mpCam = new Camera(Vector3(0.0f, 0.0f, 3.0f));

	mpInputSystem = new InputSystem(mpWindow->getWindowHandle());
	//mpLiveload = new ShaderBuild();
	mpShaderManager = new ShaderManager();

	//std::wstring directory(argv[0], argv[0] + strlen(argv[0]));
	//directory.erase(directory.find_last_of(L'\\') + 1);

	//mpLiveload->init(directory + L"RocketBuild.dll");
	//mpLiveload->addFunctionToLiveLoad("live_shader_rebuild");

	mpShaderManager->addShader(standardLightingShaderId, new RK_Shader("vLighting.glsl", "fLighting.glsl"));
	mpShaderManager->addShader(emitterShaderId, new RK_Shader("vLamp.glsl", "fLamp.glsl"));
	mpShaderManager->addShader(textShaderId, new RK_Shader("vTextRender.glsl", "fTextRender.glsl"));

	initLighting();

	processViewProjectionMatrices();

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	textObj = new Text("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId));
	TextData data = { "This is sample text", Color(127, 204, 51), Vector2(25.0f, 25.0f), 1.0f };
	textObj->initTextData(data);
	textObj2 = new Text("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId));
	data = { "(C) Rocket3d", Color(76.5f, 178.5f, 229.5f), Vector2(540.0f, 570.0f), 0.5f };
	textObj2->initTextData(data);
	// Compile and setup the shader
	Mat4 projection = MatProj::orthographic(0.0f, 800.0f, 0.0f, 600.0f);
	mpShaderManager->useShaderByKey(textShaderId);
	mpShaderManager->getShaderInUse()->setMat4("projection", projection);
	return true;
}


void EngineCore::update()
{
	//Input
	mpInputSystem->processInput();
	calculateDeltaTime();

	//Check for shader rebuild
	//TODO: shader rebuild causes need to set shader values every frame. Should fix
	//mpLiveload->pollSourceForUpdates(mpShaderManager);
}

void EngineCore::calculateDeltaTime()
{
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

//Set vertex shader uniform data for each shader
void EngineCore::processViewProjectionMatrices()
{
	mpShaderManager->useShaderByKey(standardLightingShaderId);
	Mat4 proj = Mat4::identity;
	proj = MatProj::perspective(RK_Math::degToRad(mpCam->getFov()), 800.0f / 600.0f, 0.1f, 100.0f);
	mpShaderManager->setShaderMat4("projection", proj);

	Mat4 view = Mat4::identity;
	view = mpCam->getViewMatrix();
	mpShaderManager->setShaderMat4("view", view);

	Mat4 model = Mat4::identity;

	// Light "emitters" are not affected by the lighting shader 
	// and mark the location of the light sources
	mpShaderManager->useShaderByKey(emitterShaderId);
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);

}

void EngineCore::render()
{
	mpWindow->clearToColor(0.4f, 0.6f, 0.6f, 1.0f);
	mpWindow->clearWindowBuffers(COLOR_BUFFER | DEPTH_BUFFER);
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
	mpWindow->toggleWireframe(showWireframe);
}

void EngineCore::swapBuffers()
{
	mpWindow->swapBuffers();
}