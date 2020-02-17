#ifndef MOUSE_DOWN_MSG_H
#define MOUSE_DOWN_MSG_H

#include "GameMessage.h"

class GameMouseDown : public Message {
	public:
		/*
			* The constructor requires an input keycode parameter
		*/
		GameMouseDown(const int& mouseKey, double x = 0, double y = 0);

		/*
			* Destructor
		*/
		~GameMouseDown();

		/*
			* Convert player input into an action based on the given key code.
		*/
		void process(float deltaTime);

	private:
		int mMouseCode;
		double x, y;
};

#endif // !MOUSE-
