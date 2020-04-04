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
#include <glad/glad.h>
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
#include "../asset/Model.h"


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
	delete mpGameObjectManager;
	delete mpComponentManager;

	delete textObj;
	delete textObj2;
	delete mpShaderManager;
	delete mpEditorCam;
	delete mpGameCam;
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
	mpWindowHandle = app->getAppWindow();
	mAppWindowWidth = mpWindowHandle->getWidth();
	mAppWindowHeight = mpWindowHandle->getHeight();
	
	float planeVertices[] = {
		// positions          // texture Coords 
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	   // positions   // texCoords
	   -1.0f,  1.0f,  0.0f, 1.0f,
	   -1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

	   -1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	std::shared_ptr<IndexBuffer> mPlaneIB;
	std::shared_ptr<VertexBuffer> mQuadVB, mPlaneVB;

	//init array
	mQuadVA.reset(VertexArray::create());
	//init buffer
	mQuadVB.reset(VertexBuffer::create(quadVertices, sizeof(quadVertices)));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float2, "aTexCoords" }
	};

	//store buffer
	mQuadVB->setLayout(layout);
	//add buffer
	mQuadVA->addVertexBuffer(mQuadVB);
	
	mPlaneVA.reset(VertexArray::create());	//glGenVertexArrays
	mPlaneVB.reset(VertexBuffer::create(planeVertices, sizeof(planeVertices)));
	mPlaneVB->setLayout(layout);
	mPlaneVA->addVertexBuffer(mPlaneVB);	//glBindVertexArray

	uint32 planeIndicies[6] = { 0,1,2,3,4,5 };
	mPlaneIB.reset(IndexBuffer::create(planeIndicies, sizeof(planeIndicies) / sizeof(uint32)));
	mPlaneVA->setIndexBuffer(mPlaneIB);


	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mAppWindowWidth, mAppWindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mAppWindowWidth, mAppWindowHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		RK_ERROR_ALL("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	}

	glGenFramebuffers(1, &editorFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, editorFramebuffer);
	// create a color attachment texture
	glGenTextures(1, &textureColorbuffer2);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mAppWindowWidth, mAppWindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer2, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo2;
	glGenRenderbuffers(1, &rbo2);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo2);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mAppWindowWidth, mAppWindowHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo2); // now actually attach it

	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		RK_ERROR_ALL("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	floorTexture = Model::TextureFromFile("metal.png", "../../assets/textures");

	mpGameCam = new Camera(rkm::Vector3(0.0f, 0.0f, 3.0f));
	mpEditorCam = new Camera(rkm::Vector3(-1.5f, -0.5f, 2.0f));

//	mpInputSystem = new InputSystem(mpWindowHandle->getWindowHandle());
	mpShaderManager = new ShaderManager();

	mpShaderManager->addShader(standardLightingShaderId, new RK_Shader("vFrameBuffer.glsl", "fFrameBuffer.glsl"));
	mpShaderManager->addShader("f", new RK_Shader("vFrameBuffer.glsl", "fFrameBuffer.glsl"));
	mpShaderManager->addShader("framebuffer", new RK_Shader("vFrameBufferScreen.glsl", "fFrameBufferScreen.glsl"));
	mpShaderManager->addShader(emitterShaderId, new RK_Shader("vLamp.glsl", "fLamp.glsl"));
	mpShaderManager->addShader(textShaderId, new RK_Shader("vTextRender.glsl", "fTextRender.glsl"));

	mpShaderManager->useShaderByKey(standardLightingShaderId);
	mpShaderManager->setShaderInt("texture1", 0);

	mpShaderManager->useShaderByKey("framebuffer");
	mpShaderManager->setShaderInt("screenTexture", 0);

	//initLighting();

	mpGameObjectManager = new GameObjectManager(MAX_NUM_OBJECTS);
	mpComponentManager = new ComponentManager(MAX_NUM_COMPONENETS, mpShaderManager, STANDARD_SHADER_KEY);

	textObj = new Text("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId));
	TextData data = { "This is sample text", Color(127, 204, 51), rkm::Vector2(25.0f, 25.0f), 1.0f };
	textObj->initTextData(data);
	textObj2 = new Text("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId));
	data = { "(C) Rocket3d", Color(76.5f, 178.5f, 229.5f), rkm::Vector2((float)mAppWindowWidth - 140.0f, (float)mAppWindowHeight-30.0f), 0.5f };
	textObj2->initTextData(data);
	// Compile and setup the shader
	rkm::Mat4 projection = rkm::MatProj::orthographic(0.0f, (float)mAppWindowWidth, 0.0f, (float)mAppWindowHeight);
	mpShaderManager->useShaderByKey(textShaderId);
	mpShaderManager->getShaderInUse()->setMat4("projection", projection);
	return true;
}


void EngineCore::update()
{
	calculateDeltaTime();
	mpComponentManager->update(deltaTime);
	mpGameObjectManager->updateAll(deltaTime);
}

void EngineCore::calculateDeltaTime()
{
	float currentFrame = (float)Application::getInstance()->getTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

//Set vertex shader uniform data for each shader
void EngineCore::processViewProjectionMatrices(int screenType)
{
	Application* app = Application::getInstance();

	rkm::Mat4 proj = rkm::Mat4::identity;
	rkm::Mat4 view = rkm::Mat4::identity;
	rkm::Mat4 model = rkm::Mat4::identity;
	
	float fov = 1;

	if (screenType == GAME_VIEW)
	{
		fov = rkm::degToRad(mpGameCam->getFov());
		view = mpGameCam->getViewMatrix();
	}
	else if(screenType == EDITOR_VIEW)
	{
		fov = rkm::degToRad(mpEditorCam->getFov());
		view = mpEditorCam->getViewMatrix();
	}

	mpShaderManager->useShaderByKey(standardLightingShaderId);
	proj = rkm::MatProj::perspective(fov, (float)app->getAppWindow()->getWidth() / (float)app->getAppWindow()->getHeight(), 0.1f, 100.0f);

	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4 ("view", view);

	model = rkm::Mat4::scale(model, rkm::Vector3(1, 1, -1));
	model = rkm::Mat4::translate(model, rkm::Vector3(0, -1, 0));

	// floor
	mPlaneVA->bind();
//	glBindVertexArray(planeVAO);
	glBindTexture(GL_TEXTURE_2D, floorTexture); 
	mpShaderManager->setShaderMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0 , mPlaneVA->getIndexBuffer()->getCount());
	mPlaneVA->unbind();//	glBindVertexArray(0);

	// Light "emitters" are not affected by the lighting shader 
	// and mark the location of the light sources
	mpShaderManager->useShaderByKey(emitterShaderId);
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);
}


void EngineCore::beginRender(int screenType)
{
	prepFrambuffer(screenType);
	processViewProjectionMatrices(screenType);		//before drawing
}

void EngineCore::render(int screenType)
{
	beginRender(screenType);
	mpComponentManager->renderMeshes();
	renderText();
	endRender(screenType);
}

void EngineCore::endRender(int screenType)
{
	renderFramebufferScreen(screenType);
}

void EngineCore::prepFrambuffer(int screenType)
{
	mpWindowHandle->setViewport(0, 0, mAppWindowWidth, mAppWindowHeight);

	if (screenType == GAME_VIEW)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, editorFramebuffer);
	}
	mpWindowHandle->enableWindowFlags(DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	mpWindowHandle->clearWindowBuffers(COLOR_BUFFER | DEPTH_BUFFER);
}

void EngineCore::renderFramebufferScreen(int screenType)
{
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	mpWindowHandle->disableWindowFlags(DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

	// clear all relevant buffers
	//mpWindowHandle->clearToColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	mpWindowHandle->clearWindowBuffers(COLOR_BUFFER);

	//render to a texture that isn't at screen size
	//mpWindowHandle->setViewport(0, 0, mWindowWidth, mWindowHeight);

	mpShaderManager->useShaderByKey("framebuffer");
	glBindVertexArray(quadVAO);

	if (screenType == GAME_VIEW)
	{
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
		Application::getInstance()->setRenderTexture((AppWindowType)screenType, textureColorbuffer);

	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer2);	// use the color attachment texture as the texture of the quad plane
		Application::getInstance()->setRenderTexture((AppWindowType)screenType, textureColorbuffer2);

	}
	//Application::getInstance()->setRenderTexture(EDITOR_WINDOW, textureColorbuffer);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

}


void EngineCore::renderText()
{

	Application* app = Application::getInstance();

	rkm::Mat4 projection = rkm::MatProj::orthographic(0.0f, (float)app->getAppWindow()->getWidth(), 0.0f, (float)app->getAppWindow()->getHeight());
	mpShaderManager->useShaderByKey(textShaderId);
	mpShaderManager->getShaderInUse()->setMat4("projection", projection);

	textObj->renderText();
	textObj2->renderText();
}

void EngineCore::moveCameraLeft()
{
	mpGameCam->moveCameraLeft(deltaTime);
}

void EngineCore::moveCameraRight()
{
	mpGameCam->moveCameraRight(deltaTime);
}

void EngineCore::moveCameraForward()
{
	mpGameCam->moveCameraForward(deltaTime);
}

void EngineCore::moveCameraBack()
{
	mpGameCam->moveCameraBack(deltaTime);
}

void EngineCore::toggleWireframe(bool showWireframe)
{
	mpWindowHandle->toggleWireframe(showWireframe);
}
