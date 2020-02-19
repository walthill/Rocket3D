#ifndef INPUT_INTERFACE_H
#define INPUT_INTERFACE_H

class InputSender
{
	public:
		InputSender() { };
		virtual ~InputSender() { };

		virtual void onMouseMove(double xPos, double yPos) = 0;
		virtual void onMouseScroll(double xoffset, double yoffset) = 0;
	protected:
		virtual void onKeyDown(int key, int scancode, int action, int mods) = 0;
		virtual void onKeyUp(int key, int scancode, int action, int mods) = 0;
		virtual void onKeyRepeat(int key, int scancode, int action, int mods) = 0;

		virtual void onMouseDown(int button, int action, int mods) = 0;
		virtual void onMouseUp(int button, int action, int mods) = 0;

		bool mFirstMouse = true;
		double mLastX, mLastY;
};

#endif // !INPUT_INTERFACE_H
