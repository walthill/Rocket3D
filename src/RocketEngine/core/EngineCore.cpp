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

	// uncomment this call to draw in wireframe polygons.
	//mWindow->setWindowDrawMode(FRONT_AND_BACK, WIREFRAME);

	/*******
		VERTEX SHADER
	*******/

	/*******
		FRAGMENT SHADER
	*******/

	/*******
		SHADER PROGRAM - final linked version of multiple shaders combined

		activate this shader program when rendering objects.
		The activated shaders will be used during render calls
	*******/

	/*	float vertices[] = {
			//positions			 //colors
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
		};*/

	float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

	//Plane
/*	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};*/

	float vertices2[] = {
	-0.5f,  -0.5f, 0.0f,
	 0.5f,  -0.5f, 0.0f,
	 0.0f,  0.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3, //first triangle
		1, 2, 3  //second triangle
	};




	/*******
		VERTEX INPUT
		Store the vertex data within memory on the graphics card. This data is managed by a vertex buffer object named VBO
	*******/


	/*******
		VERTEX ARRAY OBJECT (VAO)

		// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
		// 1. bind Vertex Array Object
		glBindVertexArray(VAO);
		// 2. copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 3. then set our vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		[...]

		// ..:: Drawing code (in render loop) :: ..
		// 4. draw the object
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		someOpenGLFunctionThatDrawsOurTriangle();
	*******/

	//unsigned int EBO;

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO[0]);
	//the buffer type of a vertex buffer object is GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	// copy user-defined data into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*******
		ELEMENT BUFFER OBJECTS
	******/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/*******
		LINKING VERTEX ATTRIBUTES

		THE PROCESS TO DRAW AN OBJECT
		// 0. copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 1. then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 2. use our shader program when we want to render an object
		glUseProgram(shaderProgram);
		// 3. now draw the object
		someOpenGLFunctionThatDrawsOurTriangle();
	*******/

	/*
		Param 1: Zero corresponds to the (location = 0) of vert shader source code
		Param 2: Size of vertex attribute. Equal to number of values in a Vector3
		Param 3: Specifiy data type
		Param 4: Normalize the given data?
		Param 5: The space between consecutive vertex attributes
		Param 6: Buffer offset
	*/

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//position attributes
/*	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture attributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/


	/*
		GENERATING A TEXTURE
	*/
	//bind
	//unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//TEXTURE SAMPLING
	//Selects a texture pixel (texel) to map to
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//MIPMAPS & MIPMAP FILTERING
	//Downsample textures that are far away to save memory and decrease artifacting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load image
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("../../assets/textures/container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//bind
//	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);


	//TEXTURE SAMPLING
	//Selects a texture pixel (texel) to map to
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//MIPMAPS & MIPMAP FILTERING
	//Downsample textures that are far away to save memory and decrease artifacting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//load image
	int width1, height1, nrChannels1;

	unsigned char *data1 = stbi_load("../../assets/textures/awesomeface.png", &width1, &height1, &nrChannels1, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data1);


	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	
	mpShaderManager->useShaderByKey(tutShaderId);
	mpShaderManager->setShaderInt(tutShaderId, "texture1", 0);
	mpShaderManager->setShaderInt(tutShaderId, "texture2", 1);


	//	ourShader->use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	// or set it via the texture class
//	ourShader->setInt("texture1", 0);
//	ourShader->setInt("texture2", 1); 

	/*glBindVertexArray(VAO[1]);
	//the buffer type of a vertex buffer object is GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	// copy user-defined data into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	*/

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //unbind EBO
	//glBindBuffer(GL_ARRAY_BUFFER, 0); //UNBIND VBO
	//glBindVertexArray(0); //UNBIND VAO

	/*
		size of rendering window
		first two params set location of lower left corner
		second two set width and height
	*/
	
	//glViewport(0, 0, 800, 600);
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
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);

//	mShaderManager->useShaderByKey(tutShaderId);

	/*Vector3 camPos(0.0f, 0.0f, 3.0f);
	Vector3 camTarget(0.0f, 0.0f, 3.0f);
	Vector3 camDir = camPos-camTarget;
	camDir = camDir.normalize();

	Vector3 camRight = Vector3::cross(Vector3::up, camDir);
	camRight = camRight.normalize();
	Vector3 camUp = Vector3::cross(camDir, camRight);
	
	Mat4 view;
	view = Mat4::lookAt(Vector3(0.0f, 0.0f, 3.0f),
						Vector3::zero,
						Vector3::up);
	*/
	//Vector3 cameraPos = Vector3(0.0f, 0.0f, 3.0f);
	//Vector3 cameraFront = Vector3::back;// (0.0f, 0.0f, -1.0f);
//	Vector3 cameraUp = Vector3::up;

//	float rad = 10.0f;
//	float camX = (float)sin(glfwGetTime()) * rad;
//	float camZ = (float)cos(glfwGetTime()) * rad;

	Mat4 view = Mat4::identity;	
	view = mpCam->getViewMatrix();
	mpShaderManager->setShaderMat4(tutShaderId, "view", view.getMatrixValues());
	
	//view = Mat4::lookAt(Vector3(camX, 0.0f, camZ), Vector3::zero);

	//view = Mat4::lookAt(*cameraPos, *cameraPos + *cameraFront);

	//view = Mat4::translate(view, Vector3(0.0f, 0.0f, -3.0f));
	
	Mat4 proj = Mat4::identity;
	proj = MatProj::perspective(R3_Math::degToRad(mpCam->getFov()), 800.0f / 600.0f, 0.1f, 100.0f);
	mpShaderManager->setShaderMat4(tutShaderId, "projection", proj.getMatrixValues());

	/*Mat4 proj;
	proj = MatProj::perspective(DegToRad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	mShaderManager->setShaderMat4(tutShaderId, "projection", proj.getMatrixValues());
	*/

	//mShaderManager->setShaderMat4(tutShaderId, "view", view.getMatrixValues());


	glBindVertexArray(VAO[0]);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	for (int i = 0; i < 10; i++)
	{
		Mat4 model = Mat4::identity;
		model = Mat4::translate(model, cubePositions[i]);
		float angle = (float)i * 16;
		model = Mat4::rotate(model, R3_Math::degToRad(angle), Vector3(0.5f, 1.0f, 0.0f));

		mpShaderManager->setShaderMat4(tutShaderId, "model", model.getMatrixValues());

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

