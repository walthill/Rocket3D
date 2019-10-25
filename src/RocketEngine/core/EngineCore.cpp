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
#include "../asset/image/RocketImgLoader.h"
#include "../input/InputSystem.h"
//#include "../shader/ShaderBuild.h"
#include "../shader/RK_Shader.h"
#include "../shader/ShaderManager.h"
#include "../logging/RK_Log.h"
#include "../render/light/DirectionalLight.h"
#include "../render/light/Lighting.h"
#include "../render/light/PointLight.h"
#include "../render/light/SpotLight.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
	uint32 textureId;
	Vector2 size;
	Vector2 bearing;
	uint32 advance;
};
std::map<char, Character> characters;

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
	wind->rk_mouse_callback(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	EngineCore* wind = reinterpret_cast<EngineCore*>(glfwGetWindowUserPointer(window));
	wind->rk_scroll_callback(xoffset, yoffset);
}

void EngineCore::rk_scroll_callback(double xoffset, double yoffset)
{
	mpCam->processMouseScroll((float)yoffset);
}

void EngineCore::rk_mouse_callback(double xpos, double ypos)
{	
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = (float)(xpos - lastX);
	float yOffset = (float)(lastY - ypos);
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

	mpLighting = new Lighting(lightingShaderId, mpShaderManager, numPointLights);
	
	Vector3 dir, pos, ambient, diffuse, specular;
	float constant = 1.0f, linear = 0.09f, quadratic = 0.032f, 
		  cutoff = cos(RK_Math::degToRad(12.5f)), outerCutoff = cos(RK_Math::degToRad(17.5f));

	dir = Vector3(-0.2f, -1.0f, -0.3f);
	ambient = Vector3(0.075f, 0.075f, 0.075f);
	diffuse = Vector3(0.8f, 0.8f, 0.8f);
	specular = Vector3(0.5f, 0.5f, 0.5f);

	mpLighting->addDirectionalLight(new DirectionalLight(dir, ambient, diffuse, specular));

	diffuse = Vector3(0.8f, 0.8f, 0.8f);
	specular = Vector3(1.0f, 1.0f, 1.0f);

	PointLight *p;
	for(int i =0; i < numPointLights; i++)
	{
		p = new PointLight(pointLightPositions[i], ambient, diffuse, specular, constant, linear, quadratic);
		mpLighting->addPointLight(p);
	}

	//Currently acts as a flashlight
	SpotLight *s = new SpotLight(*mpCam->getFront(), Vector3::zero, Vector3::one, Vector3::one, constant, linear, quadratic, cutoff, outerCutoff);
	mpLighting->addSpotLight(s, mpCam);

	mpShaderManager->useShaderByKey(lightingShaderId);
	mpShaderManager->setShaderInt("material.diffuse", 0);
	mpShaderManager->setShaderInt("material.specular", 1);
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
	//mpLiveload = new ShaderBuild();
	mpShaderManager = new ShaderManager();

	//std::wstring directory(argv[0], argv[0] + strlen(argv[0]));
	//directory.erase(directory.find_last_of(L'\\') + 1);

	//mpLiveload->init(directory + L"RocketBuild.dll");
	//mpLiveload->addFunctionToLiveLoad("live_shader_rebuild");

	mpShaderManager->addShader(lightingShaderId, new RK_Shader("vLighting.glsl", "fLighting.glsl"));
	mpShaderManager->addShader(emitterShaderId, new RK_Shader("vLamp.glsl", "fLamp.glsl"));
	mpShaderManager->addShader(textShaderId, new RK_Shader("vTextRender.glsl", "fTextRender.glsl"));

	initLighting();

	mpModel = new Model(mMODEL_PATH + "cube/cube.obj");

	for (size_t i = 0; i < 4; i++)
	{
		mLamps.push_back(new Model(mMODEL_PATH + "cube/cube.obj"));
	}
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetFramebufferSizeCallback(mpWindow->getWindowHandle(), framebufferSizeCallback);
	glfwSetCursorPosCallback(mpWindow->getWindowHandle(), mouse_callback);
	glfwSetScrollCallback(mpWindow->getWindowHandle(), scroll_callback);

	FT_Library ft;
	if(FT_Init_FreeType(&ft))
		RK_CORE_ERROR_ALL("ERROR::FREETYPE: Could not init FreeType Library");

	FT_Face face;
	if (FT_New_Face(ft, "fonts/calibri.ttf", 0, &face))
		RK_CORE_ERROR_ALL("ERROR::FREETYPE: Failed to load font");

	FT_Set_Pixel_Sizes(face, 0, 48);

	
	for (GLubyte c = 0; c < 128; c++)
	{
		//load char glyph
		if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
		{
			RK_CORE_ERROR_ALL("ERROR::FREETYTPE: Failed to load Glyph");
			continue;
		}

		//generate texture
		uint32 texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
   					 face->glyph->bitmap.width, 
					 face->glyph->bitmap.rows, 
					 0, GL_RED, GL_UNSIGNED_BYTE, 
					 face->glyph->bitmap.buffer);
		//set texture options
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//store character
		Character charaacter = {
			texture,
			Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<char, Character>(c, charaacter));
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}


void EngineCore::update()
{
	//Input
	mpInputSystem->processInput();
	calculateDeltaTime();

	mpLighting->processLighting(mpCam);

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
	model = Mat4::translate(model, Vector3(0.0f, -2.75f, 0.0f));
	model = Mat4::scale(model, Vector3(0.2f, 0.2f, 0.2f));
	mpShaderManager->setShaderMat4("model", model);
	mpModel->drawModel(mpShaderManager->getShaderByKey(lightingShaderId));

	// Light "emitters" these objects are not affected by 
	// the lighting shader and mark the location of the light sources
	mpShaderManager->useShaderByKey(emitterShaderId);
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);

	for (auto i = 0; i < 4; i++)
	{
		model = Mat4(1.0f);
		model = Mat4::translate(model, pointLightPositions[i]);
		model = Mat4::scale(model, Vector3(0.1f, 0.1f, 0.1f));
		mpShaderManager->setShaderMat4("model", model);

		mLamps[i]->drawModel(mpShaderManager->getShaderByKey(emitterShaderId));
	}

	mpShaderManager->useShaderByKey(textShaderId);
	Mat4 uiProj = MatProj::orthographic(mpCam->getFov(), 800.0f / 600.0f, 0.1f, 100.0f);
	mpShaderManager->setShaderMat4("projection", uiProj);

	RenderText(*mpShaderManager->getShaderByKey(textShaderId), "This is sample text", 25.0f, 25.0f, 1.0f, Vector3(0.5, 0.8f, 0.2f));
	RenderText(*mpShaderManager->getShaderByKey(textShaderId), "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, Vector3(0.3, 0.7f, 0.9f));

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

void EngineCore::toggleWireframe(bool showWireframe)
{
	if (showWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void EngineCore::RenderText(RK_Shader &s, std::string text, float x, float y, float scale, Vector3 color)
{
	// Activate corresponding render state	
	s.use();
	glUniform3f(glGetUniformLocation(s.shaderID, "textColor"), color.getX(), color.getY(), color.getZ());
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		GLfloat xpos = x + ch.bearing.getX() * scale;
		GLfloat ypos = y - (ch.size.getY() - ch.bearing.getY()) * scale;

		GLfloat w = ch.size.getX() * scale;
		GLfloat h = ch.size.getY()* scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureId);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}