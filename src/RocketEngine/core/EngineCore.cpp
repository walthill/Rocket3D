#include "EngineCore.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <RocketMath/MathUtils.h>
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


//Window resize callback prototype
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void framebufferSizeCallback(GLFWwindow* window, int width, int height) //TODO: move to callback class
{
	glViewport(0, 0, width, height);
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
	
	//Init window
	window = glfwCreateWindow(800, 600, "Rocket3D", nullptr, nullptr);
	
	if (window == nullptr)
	{
		std::cout << "FAILED to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	//Init GLAD fuction pointer handling
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	mpInputSystem = new InputSystem(window);


	//Shader live build init
	liveload = new ShaderBuild();
	mShaderManager = new ShaderManager();

	std::wstring directory(argv[0], argv[0] + strlen(argv[0]));
	directory.erase(directory.find_last_of(L'\\') + 1);

	liveload->init(directory + L"RocketBuild.dll");
	liveload->addFunctionToLiveLoad("live_shader_rebuild");


//	ourShader = new RocketShader("vShader.glsl", "fShader.glsl");
	mShaderManager->addShader(tutShaderId, new RocketShader("vShader.glsl", "fShader.glsl"));
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	

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
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

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

	//position attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture attributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


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
	
	mShaderManager->useShaderByKey(tutShaderId);
	mShaderManager->setShaderInt(tutShaderId, "texture1", 0);
	mShaderManager->setShaderInt(tutShaderId, "texture2", 1);
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
	glViewport(0, 0, 800, 600);
	
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	return true;
}


void EngineCore::update()
{
	//Input
	mpInputSystem->processInput();

	//Check for shader rebuild
	//TODO: shader rebuild causes need to set shader values every frame. Should fix
	//liveload->pollSourceForUpdates(man);
}

void EngineCore::render()
{
	//Rendering

	glClearColor(0.4f, 0.6f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//		glUseProgram(shaderProgram);

		//	float timeValue = glfwGetTime();
		//	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		//	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);


	Mat4 trans = Mat4(1.0f);
//	trans = Mat4::rotate(trans, DegToRad(90.0f), Vector3(0.0f, 0.0f, 1.0f));
//	trans = Mat4::scale(trans, Vector3(0.5f, 0.5f, 0.5f));
	

	trans = Mat4::translate(trans, Vector3(0.5f, -0.5f, 0.0f));
	trans = Mat4::rotate(trans, (float)glfwGetTime(), Vector3(0.0f, 0.0f, 1.0f));
	
	//mShaderManager->useShaders();
//	mShaderManager->setShaderInt(tutShaderId, "texture1", 0);
//	mShaderManager->setShaderInt(tutShaderId, "texture2", 1);

	mShaderManager->setShaderMat4(tutShaderId, "transform", trans.getMatrixValues());

/*	old - moved into shader manager

	RocketShader *sh = mShaderManager->getShader(tutShaderId);
	unsigned int transformLoc = glGetUniformLocation(sh->shaderID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_TRUE, trans.getMatrixValues()); //GL_TRUE --> convert from row major to column major order
*/

	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	float scaleVal = abs(sin((float)glfwGetTime()));
	trans = Mat4::identity;
	trans = Mat4::translate(trans, Vector3(-0.5f, 0.5f, 0.0f));
	trans = Mat4::scale(trans, Vector3(scaleVal, scaleVal, scaleVal));

	mShaderManager->setShaderMat4(tutShaderId, "transform", trans.getMatrixValues());

	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glDrawArrays(GL_TRIANGLES, 0, 3); //draws primitives using currently active shader

	//glUseProgram(shaderProgram2);
	//glBindVertexArray(VAO[1]);
	//glDrawArrays(GL_TRIANGLES, 0, 3); //draws primitives using currently active shader

	// swap the buffers
	glfwSwapBuffers(window);
}
