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

enum WindowBufferType {	COLOR_BUFFER = 1, DEPTH_BUFFER = 2, ACCUM_BUFFER = 4, STENCIL_BUFFER = 8 };
enum WindowDrawMode { WIREFRAME = 1, VERTICES, FILL };
enum WindowDrawFace { FRONT = 1, BACK, FRONT_AND_BACK };
enum WindowCapabilityFlags { AA_MULTISAMPLE = 1, DEPTH_TEST = 2, STENCIL_TEST = 4, CULL_FACE = 8, BLEND = 16};

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
		bool initialize(int width, int height, const char* windowName, int settingsFlags = 0, bool showCursor = true);

		/***
			* Set window rendering capabilities
		***/
		void enableWindowFlags(int settingsToEnable);

		/***
			* Turn off window rendering capabilities
		***/
		void disableWindowFlags(int settingsToEnable);

		/***
			* Set window OpenGL capabilities
		***/
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

		void setScreenDimensions(int width, int height);
		void setHeight(int height);
		void setWidth(int width);

		/***
			* Returns the width of the window
		***/
		inline int getWidth() { return mWidth; }
		
		/***
			* Returns the height of the window
		***/		
		inline int getHeight() { return mHeight; }

		/***
			* Initialize GLFW library
		***/
		static void initGLFW();
		
		/***
			* Clean up GLFW library
		***/
		static void destroyGLFW();

	private:
		static bool mShouldInitGLFW;
		const int TOP_LEFT = 0;
		int mWidth = 0, mHeight = 0;
		GLFWwindow* mpWindow;
};

#endif // !WINDOW_H
