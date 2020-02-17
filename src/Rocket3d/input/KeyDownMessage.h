/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	This file is based on a similar file
	from Champlain College's EGP-410 (Game AI) course

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 KeyDownMessage.h
	=========================
	This class handles player inputs and converts those inputs into game actions.

********/

#ifndef KEY_DOWN_MSG_H
#define KEY_DOWN_MSG_H

#include "GameMessage.h"


class GameKeyDown : public Message
{
	private:
		//The input enum needed for processing player input
		int mKeyCode;

	public:
		/*
			* The constructor requires an input keycode parameter
		*/
		GameKeyDown(const int& key);
		
		/*
			* Destructor
		*/
		~GameKeyDown();
		
		/*
			* Convert player input into an action based on the given key code. 
		*/
		void process(float deltaTime);

};

#endif // !KEY_DOWN_MSG_H
