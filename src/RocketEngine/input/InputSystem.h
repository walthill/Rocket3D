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

struct GLFWwindow;

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
		void rk_scroll_callback(double xoffset, double yoffset);

		/***
			* Callback for moving the mouse
		***/
		void rk_mouse_click_callback(int button, int action, int modifier);

		/***
			* Callback for mouse movement
		***/
		void rk_mouse_move_callback(double xpos, double ypos);

		/***
			* Checks for inputs every frame and queues input message
		***/
		void processInput();

	private:
		GLFWwindow* mpWindowHandle;
		bool firstMouse;
		double lastX, lastY;
};

#endif // !INPUT_SYS_H
