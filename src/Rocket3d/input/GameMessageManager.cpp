#include "GameMessageManager.h"
#include "../core/GameApp.h"
#include "GameMessage.h"

GameMessageManager::GameMessageManager()
{
}

GameMessageManager::~GameMessageManager()
{
	std::list<GameMessage*>::iterator iter;
	for (iter = mMessages.begin(); iter != mMessages.end(); ++iter)
	{
		delete (*iter);
	}
}

void GameMessageManager::addMessage(GameMessage* pMessage, int delay)
{
	double currentTime = GameApp::getInstance()->getCurrentTime();

	//set frame numbers
	pMessage->mSubmittedTime = currentTime;
	pMessage->mScheduledTime = currentTime + delay;

	//put it in the message list
	mMessages.push_back(pMessage);

}

void GameMessageManager::processMessagesForThisFrame()
{
	double currentTime = GameApp::getInstance()->getCurrentTime();

	std::list<GameMessage*>::iterator iter = mMessages.begin();

	while (iter != mMessages.end())
	{
		if ((*iter)->getScheduledTime() <= currentTime)
		{
			(*iter)->process();
			delete (*iter);
			iter = mMessages.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
