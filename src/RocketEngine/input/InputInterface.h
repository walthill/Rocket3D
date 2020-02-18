#ifndef INPUT_INTERFACE_H
#define INPUT_INTERFACE_H

class InputInterface
{
	public:
		InputInterface() { };
		virtual ~InputInterface() { };

	protected:
		virtual void onKeyDown(int key, int scancode, int action, int mods) = 0;
		virtual void onKeyUp(int key, int scancode, int action, int mods) = 0;
		virtual void onKeyRepeat(int key, int scancode, int action, int mods) = 0;

		virtual void onMouseDown(int key, int scancode, int action, int mods) = 0;
		virtual void onMouseUp(int key, int scancode, int action, int mods) = 0;
		virtual void onMouseRepeat(int key, int scancode, int action, int mods) = 0;
};

#endif // !INPUT_INTERFACE_H
