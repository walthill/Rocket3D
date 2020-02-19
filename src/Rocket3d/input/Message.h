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
			 GameMessage.h
	=========================
	This class is the base message class. 
	It is meant to be built open by various message types (KeyDownMessages, etc). 
	This file contains the enum list of message types as well.

********/

#ifndef GAME_MSG_H
#define GAME_MSG_H

#include "../../RocketEngine/util/EngineUtils.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	BUTTON_DOWN = 0,
	MOUSE_DOWN,
	NUM_MSG_TYPES
};

enum AppMessageCategory
{
	INVALIED_CATEGORY = -1,
	GAME,
	IMGUI,
	NUM_CATEGORIES
};

enum MouseCode
{
	INVALID__MOUSE_KEY = -1,
	LEFT_MOUSE_DOWN, RIGHT_MOUSE_DOWN,
	MIDDLE_MOUSE_DOWN,
	MOUSE_SCROLL,
	NUM_MOUSE_CODES
};

enum MouseMoveCode {
	CAM_MOUSE_MOVE = 0
};

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

class Message
{
	public:
		friend class MessageManager;

		/***
			* Constructor requires a GameMessageType parameter
		***/
		Message(MessageType type);

		/***
			* Destructor
		***/
		~Message();

		/***
			* Access the scheduled time for the message
		***/
		double getScheduledTime() const { return mScheduledTime; };
		
		/***
			* Access the submitted time for the message
		***/
		double getSubmittedTime() const { return mSubmittedTime; };

	protected:
		MessageType mType;
		double mSubmittedTime;
		double mScheduledTime;

	private:
		//This function must be overwritten by every child class
		virtual void process(float deltaTime) PURE_VIRTUAL;

};

#endif // !GAME_MSG_H
