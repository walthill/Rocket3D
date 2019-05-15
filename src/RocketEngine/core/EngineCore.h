#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "../util/EngineUtils.h"

class Vector3;
class Camera;
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

		void r3_scroll_callback(double xoffset, double yoffset);
		void r3_mouse_callback(double xpos, double ypos);

		float deltaTime = 0.0f;	// Time between current frame and last frame
	private:
		int mWindowWidth, mWindowHeight;
		bool firstMouse = true;
		float lastX = 400, lastY = 300; //last mouse offset, half of width & height
		float lastFrame = 0.0f; // Time of last frame
		
		Window *mpWindow;
		InputSystem *mpInputSystem;
		Camera* mpCam;

		ShaderBuild* mpLiveload;
		ShaderManager* mpShaderManager;
		
		unsigned int lightVAO;

		unsigned int VBO, cubeVAO; //Vertex buffer object
		unsigned int EBO;
		unsigned int texture, texture1;
		Vector3 *cubePositions;
		ShaderKey tutShaderId = "tutShader", lampShaderId = "lamp";

		void calculateDeltaTime();
};

#endif // !ENGINE_CORE_H
