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
#include "../render/buffers/Texture.h"
#include "../render/buffers/Buffer.h"
#include "../../Rocket3d/core/Application.h"
#include "../render/Camera.h"
#include "GameObjectManager.h"
#include "../component/ComponentManager.h"
//#include "../asset/image/RocketImgLoader.h"
//#include "../shader/ShaderBuild.h"
#include "../shader/ShaderManager.h"
#include "RenderCore.h"
#include "../render/Text.h"
#include "Raycast.h"
#include "../asset/AssetManager.h"
#include <glad/glad.h>

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
	AssetManager::cleanInstance();
}


void EngineCore::initLighting()
{
	mpShaderManager->useShaderByKey(standardLightingShaderId);
	mpShaderManager->setShaderInt("material.diffuse", 0);
	mpShaderManager->setShaderInt("material.specular", 1);
	mpShaderManager->setShaderFloat("material.shininess", 8);


	mpShaderManager->useShaderByKey("litTexture");
	mpShaderManager->setShaderInt("material.diffuse", 0);
	mpShaderManager->setShaderInt("material.specular", 1);
	mpShaderManager->setShaderFloat("material.shininess", 16);
} 


bool EngineCore::initialize()
{

	Application* app = Application::getInstance();
	mpWindowHandle = app->getAppWindow();
	mAppWindowWidth = mpWindowHandle->getWidth();
	mAppWindowHeight = mpWindowHandle->getHeight();

	AssetManager::initInstance();
	AssetManager::getInstance()->initialize();

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
		// positions            // normals         // texcoords
		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
		 10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
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
	float transparentVertices[] = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
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


	float instancedQuadVertices[] = {
		// positions     // colors
		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
	};

#pragma endregion


	std::shared_ptr<IndexBuffer> mPlaneIB;
	std::shared_ptr<VertexBuffer> mQuadVB, mInstancedQuadVB, mInstancingVB, mPlaneVB, mSkyboxVB, mCubeVB, mGrassVB;

	//init array
	mQuadVA.reset(VertexArray::create());
	//init buffer
	mQuadVB.reset(VertexBuffer::create(quadVertices, sizeof(quadVertices)));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float2, "aTexCoords" }
	};
	BufferLayout planeLayout = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float3, "aNormal" },
		{ ShaderDataType::Float2, "aTexCoords" }
	};

	//store buffer
	mQuadVB->setLayout(layout);
	//add buffer
	mQuadVA->addVertexBuffer(mQuadVB);
	mQuadVA->processVertexBuffers();


	mPlaneVA.reset(VertexArray::create());
	mPlaneVB.reset(VertexBuffer::create(planeVertices, sizeof(planeVertices)));
	mPlaneVB->setLayout(planeLayout);
	mPlaneVA->addVertexBuffer(mPlaneVB);
	mPlaneVA->processVertexBuffers();
	mFloorTex.reset(Texture2D::create("../../assets/textures/wood.png"));

	//Render texture init
	mGameRenderTex.reset(FrameBuffer::create(mAppWindowWidth, mAppWindowHeight, 4));
	mEditorRenderTex.reset(FrameBuffer::create(mAppWindowWidth, mAppWindowHeight, 4));

	mpGameCam = new Camera(rkm::Vector3(0.0f, 0.0f, 3.0f));
	mpEditorCam = new Camera(rkm::Vector3(-.5f, 5.0f, 2.0f), rkm::Vector3::up, -88, -55);

	mpShaderManager = new ShaderManager();

	mpShaderManager->addShader(standardLightingShaderId, new RK_Shader("vLighting.glsl", "fLighting.glsl"));
	//mpShaderManager->addShader(reflectiveSkyboxShaderId, new RK_Shader("vSkyboxReflective.glsl", "fSkyboxReflective.glsl"));
	//mpShaderManager->addShader("refractionShader", new RK_Shader("vSkyboxReflective.glsl", "fSkyboxRefraction.glsl"));
	mpShaderManager->addShader("litTexture", new RK_Shader("vBasicTexture.glsl", "fLitTexture.glsl"));
	mpShaderManager->addShader("ts", new RK_Shader("vFrameBuffer.glsl", "fFrameBuffer.glsl"));
	mpShaderManager->addShader("ims", new RK_Shader("vInstancedMesh.glsl", "fFrameBuffer.glsl"));
	//mpShaderManager->addShader("basicTexture", new RK_Shader("vFrameBuffer.glsl", "fTransparentTexture.glsl"));
	//mpShaderManager->addShader("stencil", new RK_Shader("vFrameBuffer.glsl", "fStencilBuffer.glsl"));
	mpShaderManager->addShader("framebuffer", new RK_Shader("vFrameBufferScreen.glsl", "fFrameBufferScreen.glsl"));
	mpShaderManager->addShader(emitterShaderId, new RK_Shader("vLamp.glsl", "fLamp.glsl"));
	mpShaderManager->addShader(textShaderId, new RK_Shader("vTextRender.glsl", "fTextRender.glsl"));
	mpShaderManager->addShader(skyboxShaderId, new RK_Shader("vSkybox.glsl", "fSkybox.glsl"));
	//mpShaderManager->addShader("instanced", new RK_Shader("vSingleColorInstanceArray.glsl", "fSingleColor.glsl"));

	initLighting();


	mpGameObjectManager = new GameObjectManager(MAX_NUM_OBJECTS);
	mpComponentManager = new ComponentManager(MAX_NUM_COMPONENETS, mpShaderManager, "litTexture");

	mpShaderManager->useShaderByKey("litTexture");
	//	mpShaderManager->setShaderBool("blinn", isBlinnLighting);
	//mpShaderManager->setShaderBool("gammaCorrected", isGammaCorrected);
	mpShaderManager->setShaderFloat("gamma", 2.2);
	mpShaderManager->setShaderInt("texture1", 0);

	/*textObj.reset(Text::create("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId)));
	TextData data = { "This is sample text", Color(127, 204, 51), rkm::Vector2(25.0f, 25.0f), 1.0f };
	textObj->initTextData(data);
	
	textObj2.reset(Text::create("calibri.ttf", mpShaderManager->getShaderByKey(textShaderId)));
	data = { "(C) Rocket3d", Color(76.5f, 178.5f, 229.5f), rkm::Vector2((float)mAppWindowWidth - 140.0f, (float)mAppWindowHeight-30.0f), 0.5f };
	textObj2->initTextData(data);

	// Compile and setup the shader
	rkm::Mat4 projection = rkm::MatProj::orthographic(0.0f, (float)mAppWindowWidth, 0.0f, (float)mAppWindowHeight);
	mpShaderManager->useShaderByKey(textShaderId);
	mpShaderManager->getShaderInUse()->setMat4("projection", projection);
	*/
	Raycast::initEditorRaycast(mpEditorCam);
	RenderCommand::setStencilMask(0x00);	//disables writing to the stencil buffer

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
	else if (screenType == EDITOR_VIEW)
	{
		fov = rkm::degToRad(mpEditorCam->getFov());
		view = mpEditorCam->getViewMatrix();
	}

//	mpShaderManager->useShaderByKey(standardLightingShaderId);
	proj = rkm::MatProj::perspective(fov, (float)app->getAppWindow()->getWidth() / (float)app->getAppWindow()->getHeight(), 0.1f, 1000.0f);
	screenType == GAME_VIEW ? mpGameCam->storePerspectiveMatrix(proj) : mpEditorCam->storePerspectiveMatrix(proj);

	mpWindowHandle->disableWindowFlags(CULL_FACE);
	mpShaderManager->useShaderByKey("litTexture");
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);

	mpShaderManager->setShaderVec3("viewPos", *mpEditorCam->getPosition());
	model = rkm::Mat4::scale(model, rkm::Vector3(1,1,1));
	model = rkm::Mat4::translate(model, rkm::Vector3(0,-1,0));
	mpShaderManager->setShaderMat4("model", model);


	mFloorTex->bind();
	RenderCore::submit(mPlaneVA);
	mpWindowHandle->enableWindowFlags(CULL_FACE);


	mpShaderManager->useShaderByKey("emitter");
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);
}


void EngineCore::beginRender(int screenType)
{
	RenderCommand::clearColor(Color::black);
	RenderCommand::clearBuffer(Renderer::COLOR_BUFFER | Renderer::DEPTH_BUFFER | Renderer::STENCIL_BUFFER);
	RenderCore::beginScene();	//placeholder for now will take data on camera, lighting, etc

	prepFrambuffer(screenType);
	processViewProjectionMatrices(screenType);		//before drawing
}

void EngineCore::render(int screenType)
{
	beginRender(screenType);
	mpComponentManager->renderMeshes();
	//renderText();

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
	screenType == GAME_VIEW ? mGameRenderTex->bind() : mEditorRenderTex->bind();

	//rk_blue 102,153,153
	//rk_orange 224,172,51
	RenderCommand::clearColor(Color::black);
	RenderCommand::clearBuffer(Renderer::COLOR_BUFFER | Renderer::DEPTH_BUFFER);
	mpWindowHandle->enableWindowFlags(DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
}

void EngineCore::renderFramebufferScreen(int screenType)
{
	screenType == GAME_VIEW ? mGameRenderTex->blit() : mEditorRenderTex->blit();
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	mGameRenderTex->unbind();
	
	RenderCommand::clearColor(Color::blue);
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


void EngineCore::renderTransparentObjects(int screenType)
{
	rkm::Mat4 proj = screenType == GAME_VIEW ? mpGameCam->getPerspectiveMatrix() : mpEditorCam->getPerspectiveMatrix();
	rkm::Mat4 view = screenType == GAME_VIEW ? mpGameCam->getViewMatrix() : mpEditorCam->getViewMatrix();

	mpWindowHandle->disableWindowFlags(CULL_FACE);
	mpShaderManager->useShaderByKey("basicTexture");
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);

	//sort blended objects
	std::map<float, rkm::Vector3> sorted;
	for (unsigned int i = 0; i < windows.size(); i++)
	{
		float distance = rkm::Vector3(*mpEditorCam->getPosition() - windows[i]).getMagnitude();
		sorted[distance] = windows[i];
	}

	//Transparent grass
	rkm::Mat4 model = rkm::Mat4(1.0f);
	mWindowTex->bind();
	for (std::map<float, rkm::Vector3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		model = rkm::Mat4(1.0f);
		model = rkm::Mat4::translate(model, it->second);
		mpShaderManager->setShaderMat4("model", model);
		RenderCore::submit(mTransparentVA);
	}

	mpWindowHandle->enableWindowFlags(CULL_FACE);
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

void EngineCore::toggleLightingType()
{
	mpShaderManager->useShaderByKey("litTexture");
	mpShaderManager->setShaderBool("gammaCorrected", !isGammaCorrected);
	isGammaCorrected = !isGammaCorrected;
	RK_LOG_C(isGammaCorrected ? "Gamma enabled" : "Gamma disabled");

	//mpShaderManager->setShaderBool("blinn", !isBlinnLighting);
	//isBlinnLighting = !isBlinnLighting;
}
