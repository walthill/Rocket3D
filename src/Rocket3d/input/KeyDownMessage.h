#ifndef KEY_DOWN_MSG_H
#define KEY_DOWN_MSG_H

#include "GameMessage.h"

enum KeyCode
{
	INVALID_KEY = -1,
	ESC, 
	W_KEY,
	A_KEY,
	S_KEY,
	D_KEY,
	KEY_1,
	KEY_2,
	NUM_KEYCODES
};

class KeyDownMessage : public GameMessage
{
	private:
		int mKeyCode;

	public:
		KeyDownMessage(const int& key);
		~KeyDownMessage();

		void process();

};

#endif // !KEY_DOWN_MSG_H
