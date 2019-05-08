#include "EngineCore.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "../asset/image/RocketImgLoader.h"
#include <iostream>
#include "../input/InputSystem.h"

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


bool EngineCore::initialize()
{

	glfwInit();

	//Init OpenGL version settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	stbi_set_flip_vertically_on_load(true);
	//load image
	int width, height, nrChannels;
	unsigned char *data = stbi_load("../../assets/textures/container.jpg", &width, &height, &nrChannels, 0);

	//TEXTURE SAMPLING
	//Selects a texture pixel (texel) to map to
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//MIPMAPS & MIPMAP FILTERING
	//Downsample textures that are far away to save memory and decrease artifacting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//bind
//	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);


	//load image
	int width1, height1, nrChannels1;

	//TEXTURE SAMPLING
	//Selects a texture pixel (texel) to map to
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//MIPMAPS & MIPMAP FILTERING
	//Downsample textures that are far away to save memory and decrease artifacting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	unsigned char *data1 = stbi_load("../../assets/textures/awesomeface.png", &width1, &height1, &nrChannels1, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data);


	glBindVertexArray(VAO[1]);
	//the buffer type of a vertex buffer object is GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	// copy user-defined data into the currently bound buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);


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
	//processInput(window);
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

//	man->useShaders();//ourShader.use();
//		ourShader.setFloat("someUniform", 1.0f);
//		ourShader.se
	//ourShader->setInt("texture2", 1);

	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glDrawArrays(GL_TRIANGLES, 0, 3); //draws primitives using currently active shader

	//glUseProgram(shaderProgram2);
	//glBindVertexArray(VAO[1]);
	//glDrawArrays(GL_TRIANGLES, 0, 3); //draws primitives using currently active shader

	//Check and call events, swap the buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}
