#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

struct GLFWwindow;
class InputSystem;

class EngineCore
{
	public:
		EngineCore();
		~EngineCore();

		bool initialize();
		void clean();
		
		void update();
		void render();
		void processInput(GLFWwindow *window); //TODO: move input to RocketEngine

	private:
		int mWindowWidth, mWindowHeight;

		GLFWwindow *window;
		InputSystem *mpInputSystem;

		unsigned int VBO[2], VAO[2]; //Vertex buffer object
		unsigned int EBO;
		unsigned int texture, texture1;
};

#endif // !ENGINE_CORE_H
