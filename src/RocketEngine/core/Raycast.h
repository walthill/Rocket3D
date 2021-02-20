#ifndef RAYCAST_H
#define RAYCAST_H

#include <rkm/Vector4.h>

class Camera;

class Raycast
{
	public:
		Raycast();
		~Raycast();

		static void initEditorRaycast(Camera* camera);
		static rkm::Vector3 calculateScreenRay(float mouseX, float mouseY);

	private:
		//TODO: make data driven
		static const int msLeftOffset = 15;
		static const int msTopOffset = 18;
		static const int msWidthOffset = 20;
		static const int msHeightOffset = 26;
		static Camera* mpCam;
};

#endif // !RAYCAST_H
