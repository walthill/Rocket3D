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
#include "senders/AppInputSender.h"
#include "senders/GameInputSender.h"

class InputSystem : public rkutil::Trackable
{
	public:

		/***
			* Constructor that takes a GLFW Window context
		***/
		InputSystem(Window* window);

		/***
			* Callback for resizing the window
		***/
		void onMouseScroll(double xoffset, double yoffset);

		/***
			* Callback for mouse clicks
		***/
		void onMouseClick(int button, int action, int modifier, double xpos, double ypos);

		/***
			* Callback for mouse movement
		***/
		void onMouseMove(double xpos, double ypos);

		void onKeyEvent(int key, int scancode, int action, int mods);

		void onWindowResize(int width, int height);

		/***
			* Checks for inputs every frame and queues input message
		***/
		void processInput();

		inline void play() { mIsPlayMode = !mIsPlayMode; mpWindow->setCursor(!mIsPlayMode); }
		bool isPlaying() { return mIsPlayMode; }
		Window* getWindow() { return mpWindow; }

	private:
		AppInputSender* mpAppInput;
		GameInputSender* mpGameInput;

		Window* mpWindow;
		bool mIsPlayMode = true;
		bool modeSwitched = false;
};

#endif // !INPUT_SYS_H
