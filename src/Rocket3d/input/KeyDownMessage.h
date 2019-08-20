#ifndef KEY_DOWN_MSG_H
#define KEY_DOWN_MSG_H

#include "GameMessage.h"

enum KeyCode
{
	INVALID_KEY = -1,
	ESC, TAB, CTRL, LSHIFT, RSHIFT, SPACE, CAPS_LOCK, ENTER,
	KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P,
	KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L,
	KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M,
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
	NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5, 
	NUMPAD_6, NUMPAD_7, NUMPAD_8, NUMPAD_9, NUMPAD_0,
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
