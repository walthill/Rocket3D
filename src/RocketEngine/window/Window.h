#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;

class Window
{
	public:
		Window();
		~Window();

		void initialize();
		void clean();

		void swapBuffers();
	private:
		GLFWwindow* window;
};

#endif // !WINDOW_H
