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
			 GameMessage.cpp
	=========================
********/

#include "Message.h"

Message::Message(MessageType type)
	:mType(type)
	, mSubmittedTime(0)
	, mScheduledTime(0)
{
}

Message::~Message()
{
}