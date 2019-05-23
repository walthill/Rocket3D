#include "EngineCore.h"
#include "../window/Window.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../render/Camera.h"
#include "../asset/Model.h"
#include "../asset/image/RocketImgLoader.h"
#include <iostream>
#include "../input/InputSystem.h"
#include "../shader/ShaderBuild.h"
#include "../shader/RocketShader.h"
#include "../shader/ShaderManager.h"

EngineCore::EngineCore()
{
}

EngineCore::~EngineCore()
{
	clean();
}

void EngineCore::clean()
{
	//De-allocate all vertex data
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void framebufferSizeCallback(GLFWwindow* window, int width, int height) //TODO: move to callback class
{
	glViewport(0, 0, width, height);
}

//Help found here https://stackoverflow.com/questions/27387040/referencing-glfws-callback-functions-from-a-class
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	EngineCore* wind = reinterpret_cast<EngineCore*>(glfwGetWindowUserPointer(window));
	wind->r3_mouse_callback(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	EngineCore* wind = reinterpret_cast<EngineCore*>(glfwGetWindowUserPointer(window));
	wind->r3_scroll_callback(xoffset, yoffset);
}

void EngineCore::r3_scroll_callback(double xoffset, double yoffset)
{
	mpCam->processMouseScroll(yoffset);
}

void EngineCore::r3_mouse_callback(double xpos, double ypos)
{	
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastY = ypos;
	lastX = xpos;

	mpCam->processMouseMovement(xOffset, yOffset);
}

void EngineCore::initGLFW()
{
	glfwInit();

	//Init OpenGL version settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool EngineCore::initialize(char* argv[])
{
	initGLFW();

	mpWindow = new Window();
	
	if(!mpWindow->initialize(800, 600, "Rocket3D"))
		return false;

	//hide cursor
	glfwSetInputMode(mpWindow->getWindowHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//set this to use callbacks w/in member function
	glfwSetWindowUserPointer(mpWindow->getWindowHandle(), reinterpret_cast<void*>(this));//<--- right here

	mpCam = new Camera(Vector3(0.0f, 0.0f, 3.0f));
	mpInputSystem = new InputSystem(mpWindow->getWindowHandle());
	mpLiveload = new ShaderBuild();
	mpShaderManager = new ShaderManager();

	std::wstring directory(argv[0], argv[0] + strlen(argv[0]));
	directory.erase(directory.find_last_of(L'\\') + 1);

	mpLiveload->init(directory + L"RocketBuild.dll");
	mpLiveload->addFunctionToLiveLoad("live_shader_rebuild");

	mpShaderManager->addShader(tutShaderId, new RocketShader("vShader.glsl", "fShader.glsl"));

	mpShaderManager->useShaderByKey(tutShaderId);
	mpShaderManager->setShaderInt(tutShaderId, "texture1", 0);
	mpShaderManager->setShaderInt(tutShaderId, "texture2", 1);

	mModel = new Model("../../assets/models/nanosuit/scene.fbx");

	glEnable(GL_DEPTH_TEST);
	
	glfwSetFramebufferSizeCallback(mpWindow->getWindowHandle(), framebufferSizeCallback);
	glfwSetCursorPosCallback(mpWindow->getWindowHandle(), mouse_callback);
	glfwSetScrollCallback(mpWindow->getWindowHandle(), scroll_callback);

	return true;
}


void EngineCore::update()
{
	//Input
	mpInputSystem->processInput();
	calculateDeltaTime();

	//Check for shader rebuild
	//TODO: shader rebuild causes need to set shader values every frame. Should fix
	//liveload->pollSourceForUpdates(man);
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

	//Transformations
	Mat4 view = Mat4::identity;	
	Mat4 proj = Mat4::identity;

	view = mpCam->getViewMatrix();
	proj = MatProj::perspective(R3_Math::degToRad(mpCam->getFov()), 800.0f / 600.0f, 0.1f, 100.0f);

	mpShaderManager->useShaders();
	mpShaderManager->setShaderMat4(tutShaderId, "view", view.getMatrixValues());
	mpShaderManager->setShaderMat4(tutShaderId, "projection", proj.getMatrixValues());

	//Render the model
	Mat4 model = Mat4::identity;
	model = Mat4::translate(model, Vector3(0.0f, -2.75f, 0.0f));
	model = Mat4::scale(model, Vector3(0.2f, 0.2f, 0.2f));
	mpShaderManager->setShaderMat4(tutShaderId, "model", model.getMatrixValues());
	mModel->drawModel(mpShaderManager->getShaderByKey(tutShaderId));

	// swap the buffers
	mpWindow->swapBuffers();
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

