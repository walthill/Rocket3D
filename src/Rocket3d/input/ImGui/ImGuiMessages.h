#ifndef IMGUI_MESSAGES_H
#define IMGUI_MESSAGES_H

#include "../Message.h"

/*
===========================================================

			Game Mouse DOWN Messages

============================================================
*/


class ImGuiMouseDown : public Message
{
	public:
		/*
			* The constructor requires an input keycode parameter
		*/
		ImGuiMouseDown(const int& mouseKey, double x = 0, double y = 0);

		/*
			* Destructor
		*/
		~ImGuiMouseDown();

		/*
			* Convert player input into an action based on the given key code.
		*/
		void process(float deltaTime);

	private:
		int mMouseCode;
		double x, y;
};

#endif // !IMGUI_MESSAGES_H