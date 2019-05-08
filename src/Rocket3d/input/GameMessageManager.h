#ifndef GAME_MSG_MAN_H
#define GAME_MSG_MAN_H

#include <list>

class GameMessage;

class GameMessageManager
{
	public:
		GameMessageManager();
		~GameMessageManager();

		//NOTE: manager will now own the message and will handle deletion
		void addMessage(GameMessage* pMessage, int delay);
		void processMessagesForThisFrame();

	private:
		std::list<GameMessage*> mMessages;

};

#endif // !GAME_MSG_MAN_H
