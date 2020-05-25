#ifndef GAME_INPUT_SENDER_H
#define GAME_INPUT_SENDER_H

#include "../InputSender.h"
#include "../../window/Window.h"

class GameInputSender : public InputSender
{
	public:
		GameInputSender();
		~GameInputSender();

		//return bool flag in case we need to stop from polling beyond this layer
		bool handleKeyEvents(int key, int scancode, int action, int mods);
		bool handleMouseButtonEvents(int key, int action, int mods, double xpos, double ypos);

		void onMouseMove(double xPos, double yPos) override;
		void onMouseScroll(double xoffset, double yoffset) override;

		void processInput(Window* wind);

		void setPlayMode(bool isPlayMode);
		void setFirstMouse(bool firstMouse);

	private:
		bool mInPlayMode, mEnableEditorMouseMove=false;
		void onKeyDown(int key, int scancode, int action, int mods) override;
		void onKeyUp(int key, int scancode, int action, int mods) override;
		void onKeyRepeat(int key, int scancode, int action, int mods) override;

		void onMouseDown(int key, int action, int mods, double xpos, double ypos) override;
		void onMouseUp(int key, int action, int mods, double xpos, double ypos) override;
};

#endif //!GAME_INPUT_SENDER_H
