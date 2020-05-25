#ifndef RAYCAST_H
#define RAYCAST_H

class Camera;

class Raycast
{
	public:
		Raycast();
		~Raycast();

		static void initEditorRaycast(Camera* camera);
		static bool cast(int width, int height, float mouseX, float mouseY);

	private:
		static Camera* mpCam;
};

#endif // !RAYCAST_H
