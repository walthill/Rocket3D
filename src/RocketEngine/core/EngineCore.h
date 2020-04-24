/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 EngineCore.h
	=========================
	This is the header for the Rocket Engine renderer

********/

#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "../util/EngineUtils.h"
#include "GameObjectManager.h"
#include "../component/ComponentManager.h"
#include "../render/buffers/VertexArray.h"

class Camera;
class Window;
class InputSystem;
class ShaderManager;
class RK_Shader;
class Text;

/***************************************************************************//**
 * @brief The central point for RocketEngine graphics and rendering functionality
 *
 * This class is the central hub for the graphics & rendering 
 * logic of the engine. OpenG, lighting, shaders, input, 
 * and models are initalized here
 ******************************************************************************/
class EngineCore : public rkutil::Trackable
{
	public:
		enum ViewId { GAME_VIEW = 0, EDITOR_VIEW  };
		//doxygen example
		/// Empty class constructor
		EngineCore();

		/***
			* Destructor calls clean()
		***/
		~EngineCore();
		
		/***
			* Initialize engine components
		***/
		bool initialize(); //pass in data for live shader rebuilds
		
		/***
			* Destroy engine component pointers
		***/
		void clean();
		
		/***
			* Calculate engine logic every frame (input, lighting)
		***/
		void update();
		
		/***
			* Draw models and lighting data to the window
		***/
		void render(int screenType);
		
		/***
			* Draw ui elements to the window. Should be called last before SwapBuffer()
		***/
		void renderText();

		/***
			* Moves player left
		***/
		void moveCameraLeft();
		/***
			* Moves player right
		***/
		void moveCameraRight();
		/***
			* Moves player forward
		***/
		void moveCameraForward();
		/***
			* Moves player back
		***/
		void moveCameraBack();

		//Doxygen function documentation example w/ params
		/**********************************************************************//**
		 * Toggles the window flag between wireframe and full render modes.
		 *
		 * @param showWireframe Boolean flag to set render mode. Passing true renders 
		 * window in wireframe, and passing false renders the window in full
		 *************************************************************************/
		void toggleWireframe(bool showWireframe);

		inline GameObjectManager* getGameObjectManager() { return mpGameObjectManager; }
		inline ComponentManager* getComponentManager() { return mpComponentManager; }
		inline ShaderManager* getShaderManager() { return mpShaderManager; };
		inline Camera* getGameCamera() { return mpGameCam; }
		
		// Time between current frame and last frame
		float deltaTime = 0.0f;	

	private:
		const std::string mMODEL_PATH = "../../assets/models/";
		const int MAX_NUM_OBJECTS = 300, MAX_NUM_COMPONENETS = 1000, GAME_SCREEN = 0, EDITOR_SCREEN = 1;
		int mAppWindowWidth = 0, mAppWindowHeight = 0;
		float lastFrame = 0.0f; // Time of last frame
		
		unsigned int framebuffer, editorFramebuffer;
		unsigned int textureColorbuffer, textureColorbuffer2;
		unsigned int floorTexture;
		unsigned int planeVAO, planeVBO;

		// screen quad VAO
		unsigned int quadVAO, quadVBO;

		std::shared_ptr<VertexArray> mQuadVA, mPlaneVA;

		Window *mpWindowHandle;
		InputSystem *mpInputSystem;
		Camera* mpGameCam;
		Camera* mpEditorCam;
		ShaderManager* mpShaderManager;

		GameObjectManager* mpGameObjectManager;
		ComponentManager* mpComponentManager;

		ShaderKey standardLightingShaderId = "standardLightingShader", emitterShaderId = "emitter";
		Text* textObj;
		Text* textObj2;
		ShaderKey textShaderId = "textShader";

		/***
			* Helper function that initializes the lighting system
		***/
		void initLighting();

		/***
			* Calculate real time between frames
		***/
		void calculateDeltaTime();

		void processViewProjectionMatrices(int screenType);

		void beginRender(int screenType);

		/***
			* Draw models and lighting data to the window
		***/

		void endRender(int screenType);
		void prepFrambuffer(int screenType);
		void renderFramebufferScreen(int screenType);
};

#endif // !ENGINE_CORE_H
