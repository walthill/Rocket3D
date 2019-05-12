#include "Window.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>


Window::Window()
{
}

Window::~Window()
{
	clean();
}

void Window::clean()
{
}

bool Window::initialize(int width, int height, const char* windowName)
{
	w = width; 
	h = height;

	//Init window
	mWindow = glfwCreateWindow(width, height, windowName, nullptr, nullptr);

	if (mWindow == nullptr)
	{
		std::cout << "FAILED to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	setWindowToCurrent();

	//Init GLAD fuction pointer handling - requires a window for some reason?
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	setViewport(0, 0, w, h);

	return true;
}

void Window::clearWindowBuffers(int buffersToClear)
{
	if (buffersToClear & COLOR_BUFFER)
		glClear(GL_COLOR_BUFFER_BIT);
	if (buffersToClear & DEPTH_BUFFER)
		glClear(GL_DEPTH_BUFFER_BIT);
	/*if (buffersToClear & ACCUM_BUFFER)	//Seems to be deprecated in current glfw/OpenGL
		glClear(GL_ACCUM_BUFFER);*/			// http://stackoverflow.com/questions/23990366/ddg#23995804
	if (buffersToClear & STENCIL_BUFFER)
		glClear(GL_STENCIL_BUFFER_BIT);
}

void Window::clearToColor(float r, float g, float b, float a)
{
	glClearColor(0.4f, 0.6f, 0.6f, 1.0f);
}

void Window::setViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void Window::swapBuffers()
{
	// swap the buffers
	glfwSwapBuffers(mWindow);
}

void Window::setWindowDrawMode(WindowDrawFace faceToDraw, WindowDrawMode drawMode)
{
	if (faceToDraw == FRONT)
	{
		if (drawMode == WIREFRAME)
			glPolygonMode(GL_FRONT, GL_LINE);
		else if (drawMode == FILL)
			glPolygonMode(GL_FRONT, GL_FILL);
		else if (drawMode == VERTICES)
			glPolygonMode(GL_FRONT, GL_POINT);
	}
	else if (faceToDraw == BACK)
	{
		if (drawMode == WIREFRAME)
			glPolygonMode(GL_BACK, GL_LINE);
		else if (drawMode == FILL)
			glPolygonMode(GL_BACK, GL_FILL);
		else if (drawMode == VERTICES)
			glPolygonMode(GL_BACK, GL_POINT);
	}
	else if (faceToDraw == FRONT_AND_BACK)
	{
		if (drawMode == WIREFRAME)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else if (drawMode == FILL)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else if (drawMode == VERTICES)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
}

void Window::setWindowToCurrent()
{
	glfwMakeContextCurrent(mWindow);
}

GLFWwindow* Window::getWindowHandle() const
{
	return mWindow;
}