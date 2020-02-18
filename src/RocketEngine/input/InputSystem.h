/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 InputSystem.h
	=========================
	This class handles user input and converts those inputs 
	into messages with correspoding actions set using the GameMessage base class
	
********/

#ifndef INPUT_SYS_H
#define INPUT_SYS_H

#include <rkutil/Trackable.h>
#include "../window/Window.h"

class AppInput;

class InputSystem : public rkutil::Trackable
{
	public:

		/***
			* Constructor that takes a GLFW Window context
		***/
		InputSystem(GLFWwindow* window);

		/***
			* Callback for resizing the window
		***/
		void onMouseScroll(double xoffset, double yoffset);

		/***
			* Callback for mouse clicks
		***/
		void onMouseClick(int button, int action, int modifier);

		/***
			* Callback for mouse movement
		***/
		void onMouseMove(double xpos, double ypos);

		void onKeyEvent(int key, int scancode, int action, int mods);

		/***
			* Checks for inputs every frame and queues input message
		***/
		void processInput();

		//TODO: separate input polling types into files
		void pollGameInput(int key, int scancode, int action, int mods);
		void pollEditorInput(int key, int scancode, int action, int mods);

		inline void play() { mPlayMode = !mPlayMode; }

	private:
		AppInput* mpAppInput;

		GLFWwindow* mpWindowHandle;
		bool firstMouse, mPlayMode = true;
		double lastX, lastY;
};

#endif // !INPUT_SYS_H
