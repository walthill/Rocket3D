#include "GameMessage.h"

GameMessage::GameMessage(GameMessageType type)
	:mType(type)
	, mSubmittedTime(0)
	, mScheduledTime(0)
{
}

GameMessage::~GameMessage()
{
}