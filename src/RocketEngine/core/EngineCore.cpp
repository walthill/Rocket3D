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
	std::shared_ptr<VertexBuffer> mQuadVB, mInstancedQuadVB, mPlaneVB, mSkyboxVB, mCubeVB, mGrassVB;

	//init array
	mQuadVA.reset(VertexArray::create());
	//init buffer
	mQuadVB.reset(VertexBuffer::create(quadVertices, sizeof(quadVertices)));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "aPos" },
		{ ShaderDataType::Float2, "aTexCoords" }
	};

	BufferLayout instancedLayout = {
		{ ShaderDataType::Float2, "aPos" },
		{ ShaderDataType::Float3, "aColor" }
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

	mInstancedQuadVA.reset(VertexArray::create());
	mInstancedQuadVB.reset(VertexBuffer::create(instancedQuadVertices, sizeof(instancedQuadVertices)));
	mInstancedQuadVB->setLayout(instancedLayout);
	mInstancedQuadVA->addVertexBuffer(mInstancedQuadVB);

	mCubeVA.reset(VertexArray::create());
	mCubeVB.reset(VertexBuffer::create(cubeVertices, sizeof(cubeVertices)));
	mCubeVB->setLayout(cubeLayout);
	mCubeVA->addVertexBuffer(mCubeVB);

	mTransparentVA.reset(VertexArray::create());
	mGrassVB.reset(VertexBuffer::create(transparentVertices, sizeof(transparentVertices)));
	mGrassVB->setLayout(layout);
	mTransparentVA->addVertexBuffer(mGrassVB);

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

	windows.push_back(rkm::Vector3(-1.5f, -1.0f, -0.48f));
	windows.push_back(rkm::Vector3(1.5f, -1.0f, 0.51f));
	windows.push_back(rkm::Vector3(0.0f, -1.0f, 0.7f));
	windows.push_back(rkm::Vector3(-0.3f, -1.0f, -2.3f));
	windows.push_back(rkm::Vector3(0.5f, -1.0f, -0.6f));


	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			float newX = (float)x / 10.0f + offset;
			float newY = (float)y / 10.0f + offset;
			translations[index++] = rkm::Vector2(newX, newY);
		}
	}

	mWindowTex.reset(Texture2D::create("../../assets/textures/blending_transparent_window.png", Texture2D::WrapType::CLAMP_EDGE, Texture2D::WrapType::CLAMP_EDGE));

	mpGameCam = new Camera(rkm::Vector3(0.0f, 0.0f, 3.0f));
	mpEditorCam = new Camera(rkm::Vector3(-1.5f, -0.5f, 2.0f));

	mpShaderManager = new ShaderManager();

	mpShaderManager->addShader(standardLightingShaderId, new RK_Shader("vLighting.glsl", "fLighting.glsl"));
	mpShaderManager->addShader(reflectiveSkyboxShaderId, new RK_Shader("vSkyboxReflective.glsl", "fSkyboxReflective.glsl"));
	mpShaderManager->addShader("refractionShader", new RK_Shader("vSkyboxReflective.glsl", "fSkyboxRefraction.glsl"));
	mpShaderManager->addShader("basicTexture", new RK_Shader("vFrameBuffer.glsl", "fTransparentTexture.glsl"));
	mpShaderManager->addShader("stencil", new RK_Shader("vFrameBuffer.glsl", "fStencilBuffer.glsl"));
	mpShaderManager->addShader("framebuffer", new RK_Shader("vFrameBufferScreen.glsl", "fFrameBufferScreen.glsl"));
	mpShaderManager->addShader(emitterShaderId, new RK_Shader("vLamp.glsl", "fLamp.glsl"));
	mpShaderManager->addShader(textShaderId, new RK_Shader("vTextRender.glsl", "fTextRender.glsl"));
	mpShaderManager->addShader(skyboxShaderId, new RK_Shader("vSkybox.glsl", "fSkybox.glsl"));
	mpShaderManager->addShader("instanced", new RK_Shader("vSingleColorInstanced.glsl", "fSingleColor.glsl"));

	mpShaderManager->useShaderByKey("instanced");
	for (unsigned int i = 0; i < 100; i++)
	{
		mpShaderManager->setShaderVec2("offsets[" + std::to_string(i) + "]", translations[i]);
	}

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
	else if(screenType == EDITOR_VIEW)
	{
		fov = rkm::degToRad(mpEditorCam->getFov());
		view = mpEditorCam->getViewMatrix();
	}

	mpShaderManager->useShaderByKey(reflectiveSkyboxShaderId);
	proj = rkm::MatProj::perspective(fov, (float)app->getAppWindow()->getWidth() / (float)app->getAppWindow()->getHeight(), 0.1f, 100.0f);
	screenType == GAME_VIEW ? mpGameCam->storePerspectiveMatrix(proj)	: mpEditorCam->storePerspectiveMatrix(proj);

	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4 ("view", view);
	mpShaderManager->setShaderMat4("model", model);
	mpShaderManager->setShaderVec3("cameraPos", *mpEditorCam->getPosition());
	mSkyboxTex->bind();

	// floor
	mpShaderManager->useShaderByKey("basicTexture");
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);

	RenderCommand::setStencilBuffer(Renderer::BufferTestType::ALWAYS, 1, 0xFF);
	RenderCommand::setStencilMask(0xFF);

	
	model = rkm::Mat4::identity;
	model = rkm::Mat4::scale(model, rkm::Vector3(1, 1, -1));
	model = rkm::Mat4::translate(model, rkm::Vector3(0, -1, 0));

	mFloorTex->bind(); 

	mpShaderManager->setShaderMat4("model", model);

	RenderCore::submit(mPlaneVA); 


	//Stencil buffer - floor second render pass
	RenderCommand::setStencilBuffer(Renderer::BufferTestType::NOT_EQUAL, 1, 0xFF);
	RenderCommand::setStencilMask(0x00);
	
	mpShaderManager->useShaderByKey("stencil");
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);
	mFloorTex->bind();

	float scale = 1.1f;
	model = rkm::Mat4::identity;
	model = rkm::Mat4::scale(model, rkm::Vector3(scale, scale, -scale));
	model = rkm::Mat4::translate(model, rkm::Vector3(0, -1, 0));

	mpShaderManager->setShaderMat4("model", model);
	
	RenderCore::submit(mPlaneVA); 
	
	RenderCommand::setStencilMask(0xFF);
	RenderCommand::setStencilBuffer(Renderer::BufferTestType::ALWAYS, 0, 0xFF);

	renderSkybox(view, proj);

	// Light "emitters" are not affected by the lighting shader 
	// and mark the location of the light sources
	mpShaderManager->useShaderByKey(emitterShaderId);
	mpShaderManager->setShaderMat4("projection", proj);
	mpShaderManager->setShaderMat4("view", view);
}


void EngineCore::beginRender(int screenType)
{
	RenderCommand::clearColor(Color::grey);
	RenderCommand::clearBuffer(Renderer::COLOR_BUFFER | Renderer::DEPTH_BUFFER | Renderer::STENCIL_BUFFER);

	RenderCore::beginScene();	//placeholder for now will take data on camera, lighting, etc

	prepFrambuffer(screenType);
	processViewProjectionMatrices(screenType);		//before drawing
}

void EngineCore::render(int screenType)
{
	beginRender(screenType);
	mpComponentManager->renderMeshes();
	renderText();
	
	mpWindowHandle->disableWindowFlags(CULL_FACE);
	mpShaderManager->useShaderByKey("instanced");
	RenderCore::submit(mInstancedQuadVA, 100);
	mpWindowHandle->enableWindowFlags(CULL_FACE);

	endRender(screenType);
}

void EngineCore::endRender(int screenType)
{
	renderTransparentObjects(screenType);
	RenderCore::endScene();	//placeholder for now

	renderFramebufferScreen(screenType);
}

void EngineCore::prepFrambuffer(int screenType)
{
	mpWindowHandle->setViewport(0, 0, mAppWindowWidth, mAppWindowHeight);
	screenType == GAME_VIEW ? mGameRenderTex->bind() : mEditorRenderTex->bind();

	//rk_blue 102,153,153
	//rk_orange 224,172,51
	RenderCommand::clearColor(Color::grey);
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
