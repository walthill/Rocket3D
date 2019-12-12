#ifndef MOUSE_DOWN_MSG_H
#define MOUSE_DOWN_MSG_H

#include "GameMessage.h"

enum MouseCode
{
	INVALID__MOUSE_KEY = -1,
	LEFT_MOUSE_DOWN, RIGHT_MOUSE_DOWN,
	MIDDLE_MOUSE_DOWN,
	MOUSE_SCROLL,
	NUM_MOUSE_CODES
};

class MouseDownMessage : public GameMessage {
	public:
		/*
			* The constructor requires an input keycode parameter
		*/
		MouseDownMessage(const int& mouseKey, double x = 0, double y = 0);

		/*
			* Destructor
		*/
		~MouseDownMessage();

		/*
			* Convert player input into an action based on the given key code.
		*/
		void process();

	private:
		int mMouseCode;
		double x, y;
};

#endif // !MOUSE-
