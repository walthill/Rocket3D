#ifndef APP_MESSAGES_H
#define APP_MESSAGES_H

#include "../Message.h"

/*
===========================================================

			App KeyDown Messages

============================================================
*/

class AppKeyDown : public Message
{
	public:
		/*
			* The constructor requires an input keycode parameter
		*/
		AppKeyDown(const int& key);

		/*
			* Destructor
		*/
		~AppKeyDown();

		/*
			* Convert player input into an action based on the given key code.
		*/
		void process(float deltaTime);

	private:
		//The input enum needed for processing player input
		int mKeyCode;
};


#endif // !APP_MESSAGES_H
