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

#include "EngineCore.h"
#include "../window/Window.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../render/Camera.h"
#include "../asset/Model.h"
//#include "../asset/image/RocketImgLoader.h"
#include "../input/InputSystem.h"
//#include "../shader/ShaderBuild.h"
#include "../shader/RK_Shader.h"
#include "../shader/ShaderManager.h"
#include "../logging/RK_Log.h"
#include "../render/light/DirectionalLight.h"
#include "../render/light/Lighting.h"
#include "../render/light/PointLight.h"
#include "../render/light/SpotLight.h"

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
	delete[] pointLightPositions;

	delete mpModel;
	delete mpLighting;
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
	int numPointLights = 4;
	pointLightPositions = new Vector3[4]{
		Vector3(0.7f,  0.2f,  2.0f),
		Vector3(2.3f, -3.3f, -4.0f),
		Vector3(-4.0f,  2.0f, -12.0f),
		Vector3(0.0f,  -1.0f, -1.0f)
	};

	mpLighting = new Lighting(standardLightingShaderId, mpShaderManager, numPointLights);
	
	Vector3 dir, pos, ambient, diffuse, specular;
	float constant = 1.0f, linear = 0.09f, quadratic = 0.032f, 
		  cutoff = cos(RK_Math::degToRad(12.5f)), outerCutoff = cos(RK_Math::degToRad(17.5f));

	dir = Vector3(-0.2f, -1.0f, -0.3f);
	ambient = Vector3(0.075f, 0.075f, 0.075f);
	diffuse = Vector3(0.8f, 0.8f, 0.8f);
	specular = Vector3(0.5f, 0.5f, 0.5f);

	//mpLighting->addDirectionalLight(new DirectionalLight(dir, ambient, diffuse, specular));

	diffuse = Vector3(0.8f, 0.8f, 0.8f);
	specular = Vector3(1.0f, 1.0f, 1.0f);

	PointLight *p;
	for(int i =0; i < numPointLights; i++)
	{
		p = new PointLight(pointLightPositions[i], ambient, diffuse, specular, constant, linear, quadratic);
		//mpLighting->addPointLight(p);
	}

	//Currently acts as a flashlight
	//SpotLight *s = new SpotLight(*mpCam->getFront(), Vector3::zero, Vector3::one, Vector3::one, constant, linear, quadratic, cutoff, outerCutoff);
	//mpLighting->addSpotLight(s, mpCam);

	mpShaderManager->useShaderByKey(standardLightingShaderId);
	mpShaderManager->setShaderInt("material.diffuse", 0);
	mpShaderManager->setShaderInt("material.specular", 1);
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

	//initLighting();

	//mpModel = new Model(mMODEL_PATH + "nanosuit/nanosuit.obj");

	for (size_t i = 0; i < 4; i++)
	{
		//mLamps.push_back(new Model(mMODEL_PATH + "cube/cube.obj"));
	}

	return true;
}


void EngineCore::update()
{
	//Input
	mpInputSystem->processInput();
	calculateDeltaTime();

	//mpLighting->processLighting(mpCam);

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

void EngineCore::render()
{
	//Rendering

	mpWindow->clearToColor(0.4f, 0.6f, 0.6f, 1.0f);
	mpWindow->clearWindowBuffers(COLOR_BUFFER | DEPTH_BUFFER);
	
	//Set properties of cube object in 3d space
	Mat4 proj = Mat4::identity;
	proj = MatProj::perspective(RK_Math::degToRad(mpCam->getFov()), 800.0f / 600.0f, 0.1f, 100.0f);
	mpShaderManager->setShaderMat4("projection", proj);

	Mat4 view = Mat4::identity;	
	view = mpCam->getViewMatrix();
	mpShaderManager->setShaderMat4("view", view);
	
	Mat4 model = Mat4::identity;
	/*	model = Mat4::translate(model, Vector3(0.0f, -2.75f, 0.0f));
	model = Mat4::scale(model, Vector3(0.2f, 0.2f, 0.2f));
	mpShaderManager->setShaderMat4("model", model);
	mpModel->drawModel(mpShaderManager->getShaderByKey(standardLightingShaderId));
*/
	// Light "emitters" these objects are not affected by 
	// the lighting shader and mark the location of the light sources
	mpShaderManager->useShaderByKey(emitterShaderId);
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);

	for (auto i = 0; i < 4; i++)
	{
		model = Mat4(1.0f);
	//	model = Mat4::translate(model, pointLightPositions[i]);
		//model = Mat4::scale(model, Vector3(0.1f, 0.1f, 0.1f));
		//mpShaderManager->setShaderMat4("model", model);

		//mLamps[i]->drawModel(mpShaderManager->getShaderByKey(emitterShaderId));
	}

	// swap the buffers
	//mpWindow->swapBuffers();
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