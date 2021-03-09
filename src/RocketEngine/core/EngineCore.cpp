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
#include "../../Rocket3d/core/Application.h"
#include "../render/Camera.h"
//#include "../asset/image/RocketImgLoader.h"
//#include "../shader/ShaderBuild.h"
#include "../shader/ShaderManager.h"
#include "../logging/RK_Log.h"
#include "RenderCore.h"
#include "../render/Text.h"
#include "Raycast.h"

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
	
	#pragma region Vertices Definitions
	float cubeVertices[] = {
		// positions          // normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
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

	float skyboxVertices[] = {
		// positions          
	   -1.0f,  1.0f, -1.0f,
	   -1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
	   -1.0f,  1.0f, -1.0f,

	   -1.0f, -1.0f,  1.0f,
	   -1.0f, -1.0f, -1.0f,
	   -1.0f,  1.0f, -1.0f,
	   -1.0f,  1.0f, -1.0f,
	   -1.0f,  1.0f,  1.0f,
	   -1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

	   -1.0f, -1.0f,  1.0f,
	   -1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
	   -1.0f, -1.0f,  1.0f,

	   -1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
	   -1.0f,  1.0f,  1.0f,
	   -1.0f,  1.0f, -1.0f,

	   -1.0f, -1.0f, -1.0f,
	   -1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
	   -1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	float skyboxReflectiveVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	#pragma endregion


	std::shared_ptr<IndexBuffer> mPlaneIB;
	std::shared_ptr<VertexBuffer> mQuadVB, mPlaneVB, mSkyboxVB, mCubeVB;

	//init array
	mQuadVA.reset(VertexArray::create());
	//init buffer
	mQuadVB.reset(VertexBuffer::create(quadVertices, sizeof(quadVertices)));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float2, "aTexCoords" }
	};

	BufferLayout skyboxLayout = {
		{ ShaderDataType::Float3, "aPos" },
	};

	BufferLayout cubeLayout = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float3, "aNormal" },
	};

	//store buffer
	mQuadVB->setLayout(layout);
	//add buffer
	mQuadVA->addVertexBuffer(mQuadVB);

	mCubeVA.reset(VertexArray::create());
	mCubeVB.reset(VertexBuffer::create(cubeVertices, sizeof(cubeVertices)));
	mCubeVB->setLayout(cubeLayout);
	mCubeVA->addVertexBuffer(mCubeVB);

	mSkyboxVA.reset(VertexArray::create());
	mSkyboxVB.reset(VertexBuffer::create(skyboxVertices, sizeof(skyboxVertices)));
	mSkyboxVB->setLayout(skyboxLayout);
	mSkyboxVA->addVertexBuffer(mSkyboxVB);

	mPlaneVA.reset(VertexArray::create());	//glGenVertexArrays
	mPlaneVB.reset(VertexBuffer::create(planeVertices, sizeof(planeVertices)));
	mPlaneVB->setLayout(layout);
	mPlaneVA->addVertexBuffer(mPlaneVB);	//glBindVertexArray

	uint32 planeIndicies[6] = { 0,1,2,3,4,5 };
	mPlaneIB.reset(IndexBuffer::create(planeIndicies, sizeof(planeIndicies) / sizeof(uint32)));
	mPlaneVA->setIndexBuffer(mPlaneIB);
	
	//Render texture init
	mGameRenderTex.reset(FrameBuffer::create(mAppWindowWidth, mAppWindowHeight, 4));
	mEditorRenderTex.reset(FrameBuffer::create(mAppWindowWidth, mAppWindowHeight, 4));

	mFloorTex.reset(Texture2D::create("../../assets/textures/metal.png")); //	floorTexture = Model::TextureFromFile("metal.png", "../../assets/textures");

	std::vector<std::string> faces
	{
		"../../assets/textures/skybox/right.jpg",
		"../../assets/textures/skybox/left.jpg",
		"../../assets/textures/skybox/top.jpg",
		"../../assets/textures/skybox/bottom.jpg",
		"../../assets/textures/skybox/front.jpg",
		"../../assets/textures/skybox/back.jpg"
	};

	mSkyboxTex.reset(CubemapTexture::create(faces));

	mpGameCam = new Camera(rkm::Vector3(0.0f, 0.0f, 3.0f));
	mpEditorCam = new Camera(rkm::Vector3(-1.5f, -0.5f, 2.0f));

	mpShaderManager = new ShaderManager();

	mpShaderManager->addShader(standardLightingShaderId, new RK_Shader("vLighting.glsl", "fLighting.glsl"));
	mpShaderManager->addShader(reflectiveSkyboxShaderId, new RK_Shader("vSkyboxReflective.glsl", "fSkyboxReflective.glsl"));
	mpShaderManager->addShader("refractionShader", new RK_Shader("vSkyboxReflective.glsl", "fSkyboxRefraction.glsl"));
	mpShaderManager->addShader("basicTexture", new RK_Shader("vFrameBuffer.glsl", "fFrameBuffer.glsl"));
	mpShaderManager->addShader("framebuffer", new RK_Shader("vFrameBufferScreen.glsl", "fFrameBufferScreen.glsl"));
	mpShaderManager->addShader(emitterShaderId, new RK_Shader("vLamp.glsl", "fLamp.glsl"));
	mpShaderManager->addShader(textShaderId, new RK_Shader("vTextRender.glsl", "fTextRender.glsl"));
	mpShaderManager->addShader(skyboxShaderId, new RK_Shader("vSkybox.glsl", "fSkybox.glsl"));


	initLighting();
	mpShaderManager->useShaderByKey("basicTexture");
	mpShaderManager->setShaderInt("texture1", 0);

	mpShaderManager->useShaderByKey("framebuffer");
	mpShaderManager->setShaderInt("screenTexture", 0);

	mpShaderManager->useShaderByKey(reflectiveSkyboxShaderId);
	mpShaderManager->setShaderInt("skybox", 0);

	mpShaderManager->useShaderByKey(skyboxShaderId);
	mpShaderManager->setShaderInt("skybox", 0);

	mpGameObjectManager = new GameObjectManager(MAX_NUM_OBJECTS);
	mpComponentManager = new ComponentManager(MAX_NUM_COMPONENETS, mpShaderManager, STANDARD_SHADER_KEY);

	textObj.reset(Text::create("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId)));
	TextData data = { "This is sample text", Color(127, 204, 51), rkm::Vector2(25.0f, 25.0f), 1.0f };
	textObj->initTextData(data);
	
	textObj2.reset(Text::create("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId)));
	data = { "(C) Rocket3d", Color(76.5f, 178.5f, 229.5f), rkm::Vector2((float)mAppWindowWidth - 140.0f, (float)mAppWindowHeight-30.0f), 0.5f };
	textObj2->initTextData(data);

	// Compile and setup the shader
	rkm::Mat4 projection = rkm::MatProj::orthographic(0.0f, (float)mAppWindowWidth, 0.0f, (float)mAppWindowHeight);
	mpShaderManager->useShaderByKey(textShaderId);
	mpShaderManager->getShaderInUse()->setMat4("projection", projection);

	Raycast::initEditorRaycast(mpEditorCam);

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

	mpShaderManager->useShaderByKey(reflectiveSkyboxShaderId);
	proj = rkm::MatProj::perspective(fov, (float)app->getAppWindow()->getWidth() / (float)app->getAppWindow()->getHeight(), 0.1f, 100.0f);
	mpEditorCam->storePerspectiveMatrix(proj);

	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4 ("view", view);
	mpShaderManager->setShaderMat4("model", model);
	mpShaderManager->setShaderVec3("cameraPos", *mpEditorCam->getPosition());
	mSkyboxTex->bind();

	model = rkm::Mat4::scale(model, rkm::Vector3(1, 1, -1));
	model = rkm::Mat4::translate(model, rkm::Vector3(0, -1, 0));

	// floor
	mpShaderManager->useShaderByKey("basicTexture");
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);
	mPlaneVA->bind();
	mFloorTex->bind(); 

	mpShaderManager->setShaderMat4("model", model);

	RenderCore::submit(mPlaneVA); 

	mPlaneVA->unbind();

	renderSkybox(view, proj);

	// Light "emitters" are not affected by the lighting shader 
	// and mark the location of the light sources
	mpShaderManager->useShaderByKey(emitterShaderId);
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);
}


void EngineCore::beginRender(int screenType)
{
	RenderCommand::clearColor(Color(102, 153, 153));
	RenderCommand::clearBuffer(Renderer::COLOR_BUFFER | Renderer::DEPTH_BUFFER);

	RenderCore::beginScene();	//placeholder for now will take data on camera, lighting, etc

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
	RenderCore::endScene();	//placeholder for now
	renderFramebufferScreen(screenType);
}

void EngineCore::prepFrambuffer(int screenType)
{
	mpWindowHandle->setViewport(0, 0, mAppWindowWidth, mAppWindowHeight);

	if (screenType == GAME_VIEW)
	{
		mGameRenderTex->bind();
	}
	else
	{
		mEditorRenderTex->bind();
	}

	RenderCommand::clearColor(Color(102, 153, 153));
	RenderCommand::clearBuffer(Renderer::COLOR_BUFFER | Renderer::DEPTH_BUFFER);
	mpWindowHandle->enableWindowFlags(DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

}

void EngineCore::renderFramebufferScreen(int screenType)
{
	screenType == GAME_VIEW ? mGameRenderTex->blit() : mEditorRenderTex->blit();
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	mGameRenderTex->unbind();

	RenderCommand::clearColor(Color(102, 153, 153));
	RenderCommand::clearBuffer(Renderer::COLOR_BUFFER);
	mpWindowHandle->disableWindowFlags(DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.

	
	//render to a texture that isn't at screen size

	mpShaderManager->useShaderByKey("framebuffer");
	mQuadVA->bind();

	if (screenType == GAME_VIEW)
	{
		mGameRenderTex->bindScreenTexture();
		Application::getInstance()->setRenderTexture((AppWindowType)screenType, mGameRenderTex->getTexture());
	}
	else
	{
		mEditorRenderTex->bindScreenTexture(); 
		Application::getInstance()->setRenderTexture((AppWindowType)screenType, mEditorRenderTex->getTexture());
	}
}


void EngineCore::renderText()
{
	Application* app = Application::getInstance();

	rkm::Mat4 projection = rkm::MatProj::orthographic(0.0f, (float)app->getAppWindow()->getWidth(), 0.0f, (float)app->getAppWindow()->getHeight());
	mpShaderManager->useShaderByKey(textShaderId);
	mpShaderManager->setShaderMat4("projection", projection);

	textObj->renderText();
	textObj2->renderText();
}

void EngineCore::renderSkybox(rkm::Mat4 view, rkm::Mat4 proj)
{
	RenderCommand::setDepthBuffer(Renderer::BufferTestType::LESS_OR_EQUAL);
	rkm::Mat4 skyboxView = rkm::Mat4(rkm::Mat3(view));

	mpShaderManager->useShaderByKey(skyboxShaderId);
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", skyboxView);
	
	mSkyboxTex->bind();
	RenderCore::submit(mSkyboxVA);

	RenderCommand::setDepthBuffer(Renderer::BufferTestType::LESS);
}

void EngineCore::moveCameraLeft()
{
	mpGameCam->moveCameraLeft(deltaTime * 5);
}

void EngineCore::moveCameraRight()
{
	mpGameCam->moveCameraRight(deltaTime * 5);
}

void EngineCore::moveCameraForward()
{
	mpGameCam->moveCameraForward(deltaTime * 5);
}

void EngineCore::moveCameraBack()
{
	mpGameCam->moveCameraBack(deltaTime * 5);
}

void EngineCore::toggleWireframe(bool showWireframe)
{
	mpWindowHandle->toggleWireframe(showWireframe);
}
