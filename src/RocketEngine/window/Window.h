#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;

enum WindowBufferType {	COLOR_BUFFER = 1, DEPTH_BUFFER, ACCUM_BUFFER, STENCIL_BUFFER };
enum WindowDrawMode { WIREFRAME = 1, VERTICES, FILL };
enum WindowDrawFace { FRONT = 1, BACK, FRONT_AND_BACK };

class Window
{
	public:
		Window();
		~Window();

		bool initialize(int width, int height, const char* windowName);
		void clean();

		void clearToColor(float r, float g, float b, float a = 1.0f);
		void clearWindowBuffers(int buffersToClear);	

		void setViewport(int x, int y, int width, int height);
		void swapBuffers();
		void setWindowToCurrent();
		void setWindowDrawMode(WindowDrawFace faceToDraw, WindowDrawMode drawMode); //TODO(low): call this w/ user input

		GLFWwindow* getWindowHandle() const;

	private:
		int w, h;
		GLFWwindow* mWindow;
};

#endif // !WINDOW_H
