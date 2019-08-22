#ifndef INPUT_SYS_H
#define INPUT_SYS_H

#include <DeanLib/Trackable.h>

struct GLFWwindow;

class InputSystem : public Trackable
{
	public:
		InputSystem(GLFWwindow* window);
		void processInput();

	private:
		GLFWwindow* mpWindowHandle;
};

#endif // !INPUT_SYS_H
