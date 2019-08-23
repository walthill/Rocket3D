/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	This file is based on a similar file
	from Champlain College's EGP-410 (Game AI) course.

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 GameMessageManager.h
	=========================
	This class contains and processes every message queued and 
	sent across the game/engine utilizing a simple scheduling system.

********/

#ifndef GAME_MSG_MAN_H
#define GAME_MSG_MAN_H

#include <list>

class GameMessage;

class GameMessageManager
{
	public:
		GameMessageManager();
		~GameMessageManager();

		/***
			* The manager will own the message and handle processing & deletion
		***/
		void addMessage(GameMessage* pMessage, int delay);

		/***
			* Execute the logic of the queued messages. Messages are processed
			based on the delay time passed into addMessage()
		***/
		void processMessagesForThisFrame();

	private:
		std::list<GameMessage*> mMessages;

};

#endif // !GAME_MSG_MAN_H
