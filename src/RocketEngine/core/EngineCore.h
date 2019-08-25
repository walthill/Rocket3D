#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

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
		EngineCore();
		~EngineCore();
		
		void initLighting();
		void initGLFW();

		bool initialize(char* argv[]); //pass in data for live shader rebuilds
		void clean();
		void update();
		void render();

		void moveCameraLeft();
		void moveCameraRight();
		void moveCameraForward();
		void moveCameraBack();
		void toggleWireframe(bool showWireframe);

		void rk_scroll_callback(double xoffset, double yoffset);
		void rk_mouse_callback(double xpos, double ypos);

		float deltaTime = 0.0f;	// Time between current frame and last frame
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
		ShaderKey lightingShaderId = "lightingShader", emitterShaderId = "emmiter";
		
		Model* mpModel;
		std::vector<Model*> mLamps;

		void calculateDeltaTime();
};

#endif // !ENGINE_CORE_H
