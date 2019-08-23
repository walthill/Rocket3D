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

enum KeyCode
{
	INVALID_KEY = -1,
	ESC, TAB, CTRL, LSHIFT, RSHIFT, SPACE, CAPS_LOCK, ENTER,
	KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P,
	KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L,
	KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M,
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
	NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5, 
	NUMPAD_6, NUMPAD_7, NUMPAD_8, NUMPAD_9, NUMPAD_0,
	NUM_KEYCODES
};

class KeyDownMessage : public GameMessage
{
	private:
		//The input enum needed for processing player input
		int mKeyCode;

	public:
		/*
			* The constructor requires an input keycode parameter
		*/
		KeyDownMessage(const int& key);
		
		/*
			* Destructor
		*/
		~KeyDownMessage();
		
		/*
			* Convert player input into an action based on the given key code. 
		*/
		void process();

};

#endif // !KEY_DOWN_MSG_H
