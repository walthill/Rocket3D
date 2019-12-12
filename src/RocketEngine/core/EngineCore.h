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

********/

#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

//See RocketImgLoader.h
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "../util/EngineUtils.h"

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

		//doxygen example
		/// Empty class constructor
		EngineCore();

		/***
			* Destructor calls clean()
		***/
		~EngineCore();
		
		/***
			* Initialize GLFW and set OpenGL flags
		***/
		void initGLFW();

		/***
			* Initialize engine components
		***/
		bool initialize(float windowWidth, float windowHeight); //pass in data for live shader rebuilds
		
		/***
			* Destroy engine component pointers
		***/
		void clean();
		
		/***
			* Calculate engine logic every frame (input, lighting)
		***/
		void update();
		
		void processViewProjectionMatrices();


		/***
			* Draw models and lighting data to the window
		***/
		void render();

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

		/***
			* Callback for resizing the window
		***/
	//	void rk_scroll_callback(double xoffset, double yoffset);

		//void rk_mouse_click_callback(int button, int action, int modifier);


		/***
			* Callback for mouse movement
		***/
		//void rk_mouse_move_callback(double xpos, double ypos);

		ShaderManager* getShaderManager() { return mpShaderManager; };
		Camera* getCamera() { return mpCam; }
		void swapBuffers();

		// Time between current frame and last frame
		float deltaTime = 0.0f;	

	private:
		const std::string mMODEL_PATH = "../../assets/models/";
		uint32 VAO, VBO;
		float mWindowWidth, mWindowHeight;
		float lastFrame = 0.0f; // Time of last frame
		
		Window *mpWindow;
		InputSystem *mpInputSystem;
		Camera* mpCam;

		ShaderManager* mpShaderManager;
		
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
};

#endif // !ENGINE_CORE_H
