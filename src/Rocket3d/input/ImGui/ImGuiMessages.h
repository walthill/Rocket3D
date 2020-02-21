#ifndef IMGUI_MESSAGES_H
#define IMGUI_MESSAGES_H

#include "../Message.h"

/*
===========================================================

			ImGui Key UP Messages

============================================================
*/


class ImGuiKeyUp : public Message
{
	public:
		/*
			* The constructor requires an input keycode parameter
		*/
		ImGuiKeyUp(const int& key);

		/*
			* Destructor
		*/
		~ImGuiKeyUp();

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

			ImGui Key DOWN Messages

============================================================
*/


class ImGuiKeyDown : public Message
{
public:
	/*
		* The constructor requires an input keycode parameter
	*/
	ImGuiKeyDown(const int& key, const int& mod = 0);

	/*
		* Destructor
	*/
	~ImGuiKeyDown();

	/*
		* Convert player input into an action based on the given key code.
	*/
	void process(float deltaTime);

private:
	//The input enum needed for processing player input
	int mKeyCode, mKeyMod;
};


/*
===========================================================

			ImGui Mouse DOWN Messages

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

/*
===========================================================

			ImGui Mouse UP Messages

============================================================
*/


class ImGuiMouseUp : public Message
{
public:
	/*
		* The constructor requires an input keycode parameter
	*/
	ImGuiMouseUp(const int& mouseKey, double x = 0, double y = 0);

	/*
		* Destructor
	*/
	~ImGuiMouseUp();

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

			ImGui Mouse DOWN Messages

============================================================
*/


class ImGuiMouseMove : public Message
{
public:
	/*
		* The constructor requires an input keycode parameter
	*/
	ImGuiMouseMove(const int& mouseKey, double x = 0, double y = 0);

	/*
		* Destructor
	*/
	~ImGuiMouseMove();

	/*
		* Convert player input into an action based on the given key code.
	*/
	void process(float deltaTime);

private:
	int mMouseMoveCode;
	double xPos, yPos;
};

class ImGuiUilityMsg : public Message
{
public:
	/*
		* The constructor requires an input keycode parameter
	*/
	ImGuiUilityMsg(const int& mouseKey, double x = 0, double y = 0);

	/*
		* Destructor
	*/
	~ImGuiUilityMsg();

	/*
		* Convert player input into an action based on the given key code.
	*/
	void process(float deltaTime);

private:
	int mUtilCode;
	double mX, mY;
};


#endif // !IMGUI_MESSAGES_H
