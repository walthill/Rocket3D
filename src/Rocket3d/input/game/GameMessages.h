#ifndef GAME_MESSAGES_H
#define GAME_MESSAGES_H

#include "../Message.h"


/*
===========================================================

			Game Key DOWN Messages

============================================================
*/


class GameKeyDown : public Message
{
	public:
		/*
			* The constructor requires an input keycode parameter
		*/
		GameKeyDown(const int& key);

		/*
			* Destructor
		*/
		~GameKeyDown();

		/*
			* Convert player input into an action based on the given key code.
		*/
		void process(float deltaTime);

	private:
		//The input enum needed for processing player input
		int mKeyCode;
};


/*
===========================================================

			Game Mouse DOWN Messages

============================================================
*/


class GameMouseDown : public Message 
{
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


/*
===========================================================

			Game Mouse MOVE Messages

============================================================
*/


class GameMouseMove : public Message 
{
	public:
		/*
			* The constructor requires an input keycode parameter
		*/
		GameMouseMove(const int& mouseKey, double x = 0, double y = 0);

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


#endif // !GAME_MESSAGES_H
