#ifndef RAYCAST_H
#define RAYCAST_H

class Raycast
{
	public:
		Raycast();
		~Raycast();

		static bool cast(int width, int height, float mouseX, float mouseY);

	private:
};

#endif // !RAYCAST_H
