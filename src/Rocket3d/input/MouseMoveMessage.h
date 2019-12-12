#ifndef MOUSE_MOVE_MSG_H
#define MOUSE_MOVE_MSG_H

#include "GameMessage.h"

enum MouseMoveCode {
	CAM_MOUSE_MOVE = 0
};

class MouseMoveMessage : public GameMessage {
	public:
	/*
		* The constructor requires an input keycode parameter
	*/
	MouseMoveMessage(const int& key, double x = 0, double y = 0);

	/*
		* Destructor
	*/
	~MouseMoveMessage();

	/*
		* Convert player input into an action based on the given key code.
	*/
	void process();

private:
	int mMouseMoveCode;
	float xPos, yPos;
};

#endif // !MOUSE_MOVE_MSG_H
