#include "EngineCore.h"
#include "../window/Window.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../render/Camera.h"
//#include <RocketMath/MathUtils.h>
#include "../asset/image/RocketImgLoader.h"
#include <iostream>
#include "../input/InputSystem.h"
#include "../shader/ShaderBuild.h"
#include "../shader/RK_Shader.h"
#include "../shader/ShaderManager.h"
#include "../render/light/DirectionalLight.h"
#include "../render/light/Lighting.h"

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
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();
}

unsigned int loadTexture(const char *path);
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

	mpShaderManager->addShader(tutShaderId, new RK_Shader("vLighting.glsl", "fLighting.glsl"));
	mpShaderManager->addShader("lamp", new RK_Shader("vLamp.glsl", "fLamp.glsl"));


	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	
	cubePositions = new Vector3[10]{
	Vector3(0.0f,  0.0f,  0.0f),
	Vector3(2.0f,  5.0f, -15.0f),
	Vector3(-1.5f, -2.2f, -2.5f),
	Vector3(-3.8f, -2.0f, -12.3f),
	Vector3(2.4f, -0.4f, -3.5f),
	Vector3(-1.7f,  3.0f, -7.5f),
	Vector3(1.3f, -2.0f, -2.5f),
	Vector3(1.5f,  2.0f, -2.5f),
	Vector3(1.5f,  0.2f, -1.5f),
	Vector3(-1.3f,  1.0f, -1.5f)
	};

	pointLightPositions = new Vector3[4]{
		Vector3(0.7f,  0.2f,  2.0f),
		Vector3(2.3f, -3.3f, -4.0f),
		Vector3(-4.0f,  2.0f, -12.0f),
		Vector3(0.0f,  0.0f, -3.0f)
	};

	//Init cube vertices
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	//the buffer type of a vertex buffer object is GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copy user-defined data into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(cubeVAO);
	// position attribute
	//Param 6 is the "stride", the step between the vertex attribute
	//Param 5 is the overall size of a single vertex array in bytes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Init lamp vertices
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// we only need to bind to the VBO, the container's VBO's data already contains the correct data.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// set the vertex attributes (only position data for our lamp)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//load image
	diffuseMap = loadTexture("../../assets/textures/container2.png");
	specMap = loadTexture("../../assets/textures/container2_specular.png");

	glEnable(GL_DEPTH_TEST);


	Vector3 dir, ambient, diffuse, specular;
	dir = Vector3(-0.2f, -1.0f, -0.3f);
	ambient = Vector3(0.05f, 0.05f, 0.05f);
	diffuse = Vector3(0.4f, 0.4f, 0.4f);
	specular = Vector3(0.5f, 0.5f, 0.5f);

	d = new DirectionalLight(dir, ambient, diffuse, specular);

	lighting = new Lighting(tutShaderId, mpShaderManager);
	lighting->addLight(d);

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

	lighting->processLighting(mpCam);

	// point light 1
	mpShaderManager->setShaderVec3("pointLights[0].position", pointLightPositions[0]);
	mpShaderManager->setShaderVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	mpShaderManager->setShaderVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	mpShaderManager->setShaderVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	mpShaderManager->setShaderFloat("pointLights[0].constant", 1.0f);
	mpShaderManager->setShaderFloat("pointLights[0].linear", 0.09);
	mpShaderManager->setShaderFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	mpShaderManager->setShaderVec3("pointLights[1].position", pointLightPositions[1]);
	mpShaderManager->setShaderVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	mpShaderManager->setShaderVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	mpShaderManager->setShaderVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	mpShaderManager->setShaderFloat("pointLights[1].constant", 1.0f);
	mpShaderManager->setShaderFloat("pointLights[1].linear", 0.09);
	mpShaderManager->setShaderFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	mpShaderManager->setShaderVec3("pointLights[2].position", pointLightPositions[2]);
	mpShaderManager->setShaderVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	mpShaderManager->setShaderVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	mpShaderManager->setShaderVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	mpShaderManager->setShaderFloat("pointLights[2].constant", 1.0f);
	mpShaderManager->setShaderFloat("pointLights[2].linear", 0.09);
	mpShaderManager->setShaderFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	mpShaderManager->setShaderVec3("pointLights[3].position", pointLightPositions[3]);
	mpShaderManager->setShaderVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	mpShaderManager->setShaderVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	mpShaderManager->setShaderVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	mpShaderManager->setShaderFloat("pointLights[3].constant", 1.0f);
	mpShaderManager->setShaderFloat("pointLights[3].linear", 0.09);
	mpShaderManager->setShaderFloat("pointLights[3].quadratic", 0.032);
	// spotLight
	mpShaderManager->setShaderVec3("spotLight.position", mpCam->getPosition());
	mpShaderManager->setShaderVec3("spotLight.direction", *mpCam->getFront());
	mpShaderManager->setShaderVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	mpShaderManager->setShaderVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	mpShaderManager->setShaderVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	mpShaderManager->setShaderFloat("spotLight.constant", 1.0f);
	mpShaderManager->setShaderFloat("spotLight.linear", 0.09);
	mpShaderManager->setShaderFloat("spotLight.quadratic", 0.032);
	mpShaderManager->setShaderFloat("spotLight.cutOff", cos(RK_Math::degToRad(12.5f)));
	mpShaderManager->setShaderFloat("spotLight.outerCutOff", cos(RK_Math::degToRad(15.0f)));



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
	mpWindow->clearToColor(0.1f, 0.1f, 0.1f);
	mpWindow->clearWindowBuffers(COLOR_BUFFER | DEPTH_BUFFER);
	
	//Set properties of cube object in 3d space
	Mat4 proj = Mat4::identity;
	proj = MatProj::perspective(RK_Math::degToRad(mpCam->getFov()), 800.0f / 600.0f, 0.1f, 100.0f);
	mpShaderManager->setShaderMat4("projection", proj);

	Mat4 view = Mat4::identity;	
	view = mpCam->getViewMatrix();
	mpShaderManager->setShaderMat4("view", view);
	
	Mat4 model = Mat4::identity;
	
	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specMap);

	//draw cube
	glBindVertexArray(cubeVAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		model = Mat4(1.0f);
		model = Mat4::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = Mat4::rotate(model, RK_Math::degToRad(angle), Vector3(1.0f, 0.3f, 0.5f));
		mpShaderManager->setShaderMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//Lamp - light source
	//Set 3d properties
	mpShaderManager->useShaderByKey(lampShaderId);
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);

	//Draw
	glBindVertexArray(lightVAO);
	for (unsigned int i = 0; i < 4; i++)
	{
		model = Mat4(1.0f);
		model = Mat4::translate(model, pointLightPositions[i]);
		model = Mat4::scale(model, Vector3(0.2f, 0.2f, 0.2f));
		mpShaderManager->setShaderMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

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

void EngineCore::moveCameraBack() //S
{
	mpCam->moveCameraBack(deltaTime);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}