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

	This class is the central point for the graphics & rendering 
	logic of the engine. OpenG, lighting, shaders, input, 
	and models are initalized here

********/

#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

//See RocketImgLoader.h
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "../util/EngineUtils.h"

class Vector3;
class Camera;
class Window;
class InputSystem;
class ShaderBuild;
class Lighting;
class DirectionalLight;
class PointLight;
class SpotLight;
class ShaderManager;
class RK_Shader;
class Model;

class EngineCore : public Trackable
{
	public:
		/***
			* Empty Constructor
		***/
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
		bool initialize(char* argv[]); //pass in data for live shader rebuilds
		
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

		/***
			* View models in wireframe
		***/
		void toggleWireframe(bool showWireframe);

		/***
			* Callback for resizing the window
		***/
		void rk_scroll_callback(double xoffset, double yoffset);

		/***
			* Callback for mouse movement
		***/
		void rk_mouse_callback(double xpos, double ypos);

		ShaderManager* getShaderManager() { return mpShaderManager; };
		void swapBuffers();


		// Time between current frame and last frame
		float deltaTime = 0.0f;	

	private:
		const std::string mMODEL_PATH = "../../assets/models/";

		int mWindowWidth, mWindowHeight;
		bool firstMouse = true;
		double lastX = 400, lastY = 300; //last mouse offset, half of width & height
		float lastFrame = 0.0f; // Time of last frame
		
		Window *mpWindow;
		InputSystem *mpInputSystem;
		Camera* mpCam;

		//ShaderBuild* mpLiveload;
		ShaderManager* mpShaderManager;
		Lighting* mpLighting;
		
		Vector3 *pointLightPositions;
		ShaderKey standardLightingShaderId = "standardLightingShader", emitterShaderId = "emmiter";
		
		Model* mpModel;
		std::vector<Model*> mLamps;

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
