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

enum GameMessageType
{
	INVALID_MESSAGE_TYPE = -1,
	BUTTON_DOWN = 0,
	MOUSE_DOWN,
	NUM_MSG_TYPES
};

class GameMessage
{
	public:
		friend class GameMessageManager;

		/***
			* Constructor requires a GameMessageType parameter
		***/
		GameMessage(GameMessageType type);

		/***
			* Destructor
		***/
		~GameMessage();

		/***
			* Access the scheduled time for the message
		***/
		double getScheduledTime() const { return mScheduledTime; };
		
		/***
			* Access the submitted time for the message
		***/
		double getSubmittedTime() const { return mSubmittedTime; };

	protected:
		GameMessageType mType;
		double mSubmittedTime;
		double mScheduledTime;

	private:
		//This function must be overwritten by every child class
		virtual void process(float deltaTime) PURE_VIRTUAL;

};

#endif // !GAME_MSG_H
