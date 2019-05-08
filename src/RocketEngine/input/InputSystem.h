#ifndef INPUT_SYS_H
#define INPUT_SYS_H

struct GLFWwindow;

class InputSystem
{
	public:
		InputSystem(GLFWwindow* window);
		void processInput();

	private:
		GLFWwindow* mpWindowHandle;
};

#endif // !INPUT_SYS_H
