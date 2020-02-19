#ifndef IMGUI_INPUT_SENDER_H
#define IMGUI_INPUT_SENDER_H

#include "InputSender.h"

class ImGuiInputSender : public InputSender
{
	public:
		ImGuiInputSender();
		~ImGuiInputSender();

		//return bool flag in case we need to stop from polling beyond this layer
		bool handleKeyEvents(int key, int scancode, int action, int mods);
		bool handleMouseButtonEvents(int button, int action, int mods);

		void onMouseMove(double xpos, double ypos) override;
		void onMouseScroll(double xoffset, double yoffset) override;

	private:
			void onKeyDown(int key, int scancode, int action, int mods) override;
			void onKeyUp(int key, int scancode, int action, int mods) override;
			void onKeyRepeat(int key, int scancode, int action, int mods) override;

			void onMouseDown(int key, int action, int mods) override;
			void onMouseUp(int key, int action, int mods) override;
};

#endif // !IMGUI_INPUT_SENDER_H
