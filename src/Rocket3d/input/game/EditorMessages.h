#ifndef EDITOR_MESSAGES_H
#define EDITOR_MESSAGES_H

#include "../Message.h"
//TEMP
class GameObject;
/*
===========================================================

			Game Key DOWN Messages

============================================================
*/


class EditorKeyDown : public Message
{
public:
	/*
		* The constructor requires an input keycode parameter
	*/
	EditorKeyDown(const int& key);

	/*
		* Destructor
	*/
	~EditorKeyDown();

	/*
		* Convert player input into an action based on the given key code.
	*/
	void process(float deltaTime);
	static float angle;

private:
	//The input enum needed for processing player input
	int mKeyCode;
	static unsigned int id;
	static GameObject* obj;
};


/*
===========================================================

			Game Mouse DOWN Messages

============================================================
*/


class EditorMouseDown : public Message
{
public:
	/*
		* The constructor requires an input keycode parameter
	*/
	EditorMouseDown(const int& mouseKey, double x = 0, double y = 0);

	/*
		* Destructor
	*/
	~EditorMouseDown();

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


class EditorMouseMove : public Message
{
public:
	/*
		* The constructor requires an input keycode parameter
	*/
	EditorMouseMove(const int& mouseKey, double x = 0, double y = 0);

	/*
		* Destructor
	*/
	~EditorMouseMove();

	/*
		* Convert player input into an action based on the given key code.
	*/
	void process(float deltaTime);

private:
	int mMouseMoveCode;
	float xPos, yPos;
};


#endif // !GAME_MESSAGES_H
