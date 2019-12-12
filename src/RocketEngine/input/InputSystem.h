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
			* Checks for inputs every frame and queues input message
		***/
		void processInput();

	private:
		GLFWwindow* mpWindowHandle;
};

#endif // !INPUT_SYS_H
