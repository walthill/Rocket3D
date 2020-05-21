#include "Application.h"
#include "../layers/GameLayer.h"
#include <rkm/Mat4.h>

/*	TODO	
 * ============================================================
 *		
 *		
 *		
 *		-- Abstract input codes
 *		-- Input polling 
 *		-- fully implement input messaging (flesh out files, etc)
 */


Application* Application::mpApplication = nullptr;

Application::Application()
{
	mIsRunning = true;

	Window::initGLFW();
	mpMasterTimer = new rkutil::Timer();
	mpMasterTimer->start();
	
	mpAppWindow = new Window();
	mpAppWindow->initialize(1000, 750, "Rocket3D", DEPTH_TEST | AA_MULTISAMPLE | BLEND | CULL_FACE);
	mpAppWindow->clearToColor(0.4f, 0.6f, 0.6f, 1.0f);
	float arr[16] = { 1, 3, 5, 9,
					  1, 3, 1, 7,
					  4, 3, 9, 7,
					  5, 2, 0, 9 };
	rkm::Mat4 mat(arr);
	
	rkm::Mat4::invert(mat);
}

Application::~Application()
{
	clean();
}

void Application::clean()
{
	delete mpMessageManager;
	delete mpInputSystem;
	delete mpAppWindow;
	Window::destroyGLFW();
}

void Application::init()
{
	mpMessageManager = new MessageManager();
	mpInputSystem = new InputSystem(mpAppWindow);
	mpImGuiLayer = new ImGuiLayer();
	
	addOverlay(mpImGuiLayer);
	addLayer(new GameLayer());	//game layer created by default for now - TODO: add game window size (used for render tex & rendering text
}

void Application::addLayer(Layer* layer)
{
	mLayerStack.pushLayer(layer);
	layer->onAttach();
}

void Application::addOverlay(Layer* overlay)
{
	mLayerStack.pushOverlay(overlay);
	overlay->onAttach();
}

void Application::onMessage(float deltaTime)
{
	mpMessageManager->processMessagesForThisFrame(deltaTime);
}

bool Application::run()
{
	while (mIsRunning)
	{
		mpAppWindow->clearToColor(0.4f, 0.6f, 0.6f, 1.0f);
		mpAppWindow->clearWindowBuffers(COLOR_BUFFER | DEPTH_BUFFER);

		onMessage(mDeltaTime);
		mpInputSystem->processInput();
		calculateDeltaTime();

		for (Layer* layer : mLayerStack)
		{
			layer->onUpdate();
		}

		mpImGuiLayer->begin();
		for (Layer* layer : mLayerStack)
		{
			layer->onImGuiRender();
		}
		mpImGuiLayer->end();

		//swap buffer for all draw layers
		mpAppWindow->swapBuffers();
	}

	return false;
}

void Application::play()
{
	mpInputSystem->play();
}

bool Application::isPlaying()
{
	return mpInputSystem->isPlaying();
}

unsigned int Application::getRenderTexture(AppWindowType texId)
{
	unsigned int returnId = -1;

	if (texId == GAME_WINDOW)
		returnId = mGameWindowTexture;
	else if(texId == EDITOR_WINDOW)
		returnId = mEditorWindowTexture;

	return returnId;
}

void Application::setRenderTexture(AppWindowType type, unsigned int texId)
{
	if (type == GAME_WINDOW)
		mGameWindowTexture = texId;
	else if (type == EDITOR_WINDOW)
		mEditorWindowTexture = texId;
}

void Application::calculateDeltaTime()
{
	float currentFrame = (float)getTime();
	mDeltaTime = currentFrame - mLastFrame;
	mLastFrame = currentFrame;
}
