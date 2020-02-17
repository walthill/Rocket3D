#ifndef MOUSE_MOVE_MSG_H
#define MOUSE_MOVE_MSG_H

#include "GameMessage.h"

enum MouseMoveCode {
	CAM_MOUSE_MOVE = 0
};

class GameMouseMove : public Message {
	public:
	/*
		* The constructor requires an input keycode parameter
	*/
	GameMouseMove(const int& key, double x = 0, double y = 0);

	/*
		* Destructor
	*/
	~GameMouseMove();

	/*
		* Convert player input into an action based on the given key code.
	*/
	void process(float deltaTime);

private:
	int mMouseMoveCode;
	float xPos, yPos;
};

#endif // !MOUSE_MOVE_MSG_H
