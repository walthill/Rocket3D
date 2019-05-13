#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "../util/EngineUtils.h"

class Vector3;
class Window;
class InputSystem;
class ShaderBuild;
class ShaderManager;
class RocketShader;

class EngineCore
{
	public:
		EngineCore();
		~EngineCore();

		void initGLFW();
		bool initialize(char* argv[]); //pass in data for live shader rebuilds
		void clean();
		void update();
		void render();

		void moveCameraLeft();
		void moveCameraRight();
		void moveCameraForward();
		void moveCameraBack();

		float deltaTime = 0.0f;	// Time between current frame and last frame
	private:
		int mWindowWidth, mWindowHeight;

		float lastFrame = 0.0f; // Time of last frame
		float cameraSpeed = 0.25f;
		Vector3* cameraPos;// = Vector3(0.0f, 0.0f, 3.0f);
		Vector3* cameraFront;// = Vector3(0.0f, 0.0f, -1.0f);
		Vector3* cameraUp;// = Vector3(0.0f, 1.0f, 0.0f);
		
		Window *mWindow;
		InputSystem *mpInputSystem;

		ShaderBuild* liveload;
		ShaderManager* mShaderManager;
		RocketShader* ourShader;


		unsigned int VBO[2], VAO[2]; //Vertex buffer object
		unsigned int EBO;
		unsigned int texture, texture1;
		Vector3 *cubePositions;
		ShaderKey tutShaderId = "tutShader";
};

#endif // !ENGINE_CORE_H
