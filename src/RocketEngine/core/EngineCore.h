#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "../util/EngineUtils.h"

struct GLFWwindow;
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

	private:
		int mWindowWidth, mWindowHeight;

		GLFWwindow *window;
		InputSystem *mpInputSystem;

		ShaderBuild* liveload;
		ShaderManager* mShaderManager;
		RocketShader* ourShader;


		unsigned int VBO[2], VAO[2]; //Vertex buffer object
		unsigned int EBO;
		unsigned int texture, texture1;
		ShaderKey tutShaderId = "tutShader";
};

#endif // !ENGINE_CORE_H
