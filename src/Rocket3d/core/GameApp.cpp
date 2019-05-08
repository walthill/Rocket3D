#include "GameApp.h"
#include <core/EngineCore.h>
#include <iostream>
#include <DeanLib/PerformanceTracker.h>
#include "../AppShaderBuild.h"
#include "../RocketShader.h"
#include "../ShaderManager.h"
#include "../input/GameMessage.h"
#include "../input/GameMessageManager.h"

GameApp* GameApp::mpGameApp = nullptr;

GameApp::~GameApp()
{
	clean();
}


bool GameApp::initialize(char* argv[])
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
	pPerformanceTracker->startTracking(mINIT_TRACKER_NAME);

	mRocketEngine = new EngineCore();
	mpGameMessageManager = new GameMessageManager();
	
	mRocketEngine->initialize();

	//Shader live build init
	liveload = new AppShaderBuild();
	man = new ShaderManager();

	std::wstring directory(argv[0], argv[0] + strlen(argv[0]));
	directory.erase(directory.find_last_of(L'\\') + 1);

	liveload->init(directory + L"RocketBuild.dll");
	liveload->addFunctionToLiveLoad("live_shader_rebuild");

	
	ourShader = new RocketShader("vShader.glsl", "fShader.glsl");
	man->addShader(ourShader);
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader->use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	// or set it via the texture class
	ourShader->setInt("texture2", 1);

	mpMasterTimer = new Timer();

	pPerformanceTracker->stopTracking(mINIT_TRACKER_NAME);
	std::cout << std::endl << "Time to Init: " << pPerformanceTracker->getElapsedTime(mINIT_TRACKER_NAME) << " ms" << std::endl;

	delete pPerformanceTracker;

	mShouldExit = false;

	mpMasterTimer->start();

	return true;
}

void GameApp::clean()
{
	delete mpGameMessageManager;
	delete mRocketEngine;
}

bool GameApp::processLoop()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker();

	mpFrameTimer = new Timer();
	
	while (!mShouldExit)//!glfwWindowShouldClose(window))
	{
		pPerformanceTracker->clearTracker(mLOOP_TRACKER_NAME);
		pPerformanceTracker->startTracking(mLOOP_TRACKER_NAME);

		mpFrameTimer->start();

		pPerformanceTracker->clearTracker(mDRAW_TRACKER_NAME);
		pPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);
	

		update();
		render();


		pPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);
		mpFrameTimer->sleepUntilElapsed(m30_FRAME_TIME);
		pPerformanceTracker->stopTracking(mLOOP_TRACKER_NAME);

		//		mFPS = (1000.0 / pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME));
//		cout << "loop took:" << pPerformanceTracker->getElapsedTime(mLOOP_TRACKER_NAME) << "ms";
//		cout << " draw took:" << pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME) << "ms\n";

	}

	return false;
}

void GameApp::update()
{
	mRocketEngine->update();
	mpGameMessageManager->processMessagesForThisFrame();

	//Check for shader rebuild
	liveload->pollSourceForUpdates(man);
}

void GameApp::render()
{
	//Rendering
/*	glClearColor(0.4f, 0.6f, 0.6f, 1.0f);
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
*/
	man->useShaders();//ourShader.use();
//		ourShader.setFloat("someUniform", 1.0f);
//		ourShader.se
	ourShader->setInt("texture2", 1);
	mRocketEngine->render();
/*	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glDrawArrays(GL_TRIANGLES, 0, 3); //draws primitives using currently active shader

	//glUseProgram(shaderProgram2);
	//glBindVertexArray(VAO[1]);
	//glDrawArrays(GL_TRIANGLES, 0, 3); //draws primitives using currently active shader

	//Check and call events, swap the buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
*/
}

void GameApp::addInputMessage(GameMessage* msg, int delay)
{ 
	mpGameMessageManager->addMessage(msg, delay); 
};

double GameApp::getCurrentTime() 
{ 
	return mpMasterTimer->getElapsedTime(); 
};
