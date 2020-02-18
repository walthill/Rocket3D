#ifndef APP_INPUT_H
#define APP_INPUT_H

#include "../../../../RocketEngine/input/InputSender.h"

class AppInputSender : public InputSender
{
public:
	AppInputSender();	
	~AppInputSender();

	//return bool flag in case we need to stop from polling beyond this layer
	bool handleKeyEvents(int key, int scancode, int action, int mods);
	bool handleMouseButtonEvents(int key, int scancode, int action, int mods);

private:
	void onKeyDown(int key, int scancode, int action, int mods) override;
	void onKeyUp(int key, int scancode, int action, int mods) override;
	void onKeyRepeat(int key, int scancode, int action, int mods) override;

	void onMouseDown(int key, int scancode, int action, int mods) override;
	void onMouseUp(int key, int scancode, int action, int mods) override;
	void onMouseRepeat(int key, int scancode, int action, int mods) override;
};

#endif // !APP_INPUT_H
