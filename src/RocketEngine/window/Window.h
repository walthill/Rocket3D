/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This class makes use of tutorials from Learn OpenGL
	(https://learnopengl.com)

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 Window.h
	=========================
	Class to create and store the OpenGL window context & control window buffers

********/

#ifndef WINDOW_H
#define WINDOW_H

#include <rkutil/Trackable.h>

struct GLFWwindow;

enum WindowBufferType {	COLOR_BUFFER = 1, DEPTH_BUFFER, ACCUM_BUFFER, STENCIL_BUFFER };
enum WindowDrawMode { WIREFRAME = 1, VERTICES, FILL };
enum WindowDrawFace { FRONT = 1, BACK, FRONT_AND_BACK };
enum WindowCapabilityFlags { AA_MULTISAMPLE = 1, DEPTH_TEST, CULL_FACE, BLEND };

class Window : public rkutil::Trackable
{
	public:
		/* Empty constructor */
		Window();

		/* Empty deconstructor */
		~Window();

		/***
			* Initialize GLFW Window and OpenGL base
		****/
		bool initialize(float width, float height, const char* windowName, int settingsFlags = 0, bool showCursor = true);

		/***
			* Set window OpenGL capabilities
		***/
		void enableOpenGLWindowFlags(int settingsToEnable);

		void clean();

		/***
			* Draw a color to the screen
		****/
		void clearToColor(float r, float g, float b, float a = 1.0f);

		/***
			* Clear OpenGL render buffers based on specified bit parameter
		****/
		void clearWindowBuffers(int buffersToClear);

		/***
			* Set size of this window
		***/
		void setViewport(int x, int y, int width, int height);
		
		/***
			* Flip double buffer and display rendered visuals
		***/
		void swapBuffers();
		
		/***
			* Set this window as the in-focus window
		***/
		void setWindowToCurrent();
		
		/***
			* Set how window draws faces and vertices
		***/
		void setWindowDrawMode(WindowDrawFace faceToDraw, WindowDrawMode drawMode); //TODO(low): call this w/ user input

		/***
			* Set cursor visibility
		***/
		void setCursor(bool shouldAppear);

		/***
			* Show full polygons or vertex wireframe
		***/
		void toggleWireframe(bool showWireframe);

		/***
			* Returns pointer to the window
		***/
		GLFWwindow* getWindowHandle() const;

	private:
		const int TOP_LEFT = 0;
		int w, h;
		GLFWwindow* mWindow;
};

#endif // !WINDOW_H
